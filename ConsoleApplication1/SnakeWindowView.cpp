#include "SnakeWindowView.h"
#include "SnakeController.h"
#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

#define ID_HOTKEY 1
#define FIELDPIXELMOD 30
#define WM_UPDATEMESSAGE 155323


static SnakeController* cntrl;

SnakeWindowView::SnakeWindowView(int w, int h, HINSTANCE hInstance, SnakeController* controller)
{
	WIDTH = w;
	HEIGHT = h;
	this->length = w * h;
	this->hInstance = hInstance;

	cntrl = controller;
	

	this->mainHandle = mainWindow();
	this->RegisterGridClass();
	this->grid = initGrid();
	this->contextGrid = initContextGrid();
}


SnakeWindowView::~SnakeWindowView()
{
	delete this->contextGrid;
	delete this->grid;
}


int SnakeWindowView::refreshIndex(int index)
{
	SendMessage(this->grid[index],WM_ERASEBKGND, (UINT_PTR)this->contextGrid[index], NULL);
	return 0;
}

HWND SnakeWindowView::mainWindow()
{
	//handle zum Fenster, das wir öffnen wollen
	HWND hwnd;
	//Fenster-Klasse. Hier kommt Konfiguration rein, damit windows weiß, wie wir das Fenster haben wollen
	//davon können mehrere erstellt werden. Es ist NICHT ein Fenster, es ist die Vorlage für ein Fenster
	WNDCLASSW wc;
	//zeichne neu, wenn bewegt oder verändert
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//Unterklassen-Values
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//Name
	wc.lpszClassName = L"Window";
	//handle-Instanz, aus main
	wc.hInstance = hInstance;
	//Hintergrund-Färben
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//kein Menü
	wc.lpszMenuName = NULL;
	//function-pointer für message-callback procedure = unsere unten definierte Function
	wc.lpfnWndProc = SnakeWindowView::MainWndProc;
	//Mauszeiger auf default
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Fenster Icon default
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//Fenster registrieren, damit das OS damit kommunizieren und es anzeigen kann
	RegisterClassW(&wc);
	//Fenster erstellen mit Werten: wc.lpszClassName sorgt dafür, dass unsere Fenster-Vorlage benutzt wird, Referenz auf dieses Fenster
	//wird dann in hwnd gespeichert (handle)
	hwnd = CreateWindow(wc.lpszClassName, L"Windows",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, this->WIDTH*FIELDPIXELMOD, this->HEIGHT*FIELDPIXELMOD, 0, 0, hInstance, NULL);

	return hwnd;
}





HDC* SnakeWindowView::initContextGrid()
{
	HDC* retGrid = new HDC[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		retGrid[i] = GetWindowDC(this->grid[i]);
	}


	return retGrid;
}

LRESULT CALLBACK SnakeWindowView::MainWndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	static int ret;
	switch (msg) {
	case WM_KEYDOWN:

		switch (wParam) {
		case VK_ESCAPE: 
			ret = MessageBoxW(hwnd, L"Are you sure to quit?",
				L"Message", MB_OKCANCEL);

			if (ret == IDOK) {
				cntrl->esc();
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}
			break;
		case 0x46: 
			//PAUSE -> F-key
			break;
		case VK_SPACE:
			cntrl->spaceBar();
			break;
		case VK_LEFT:
			cntrl->left();
			break;
		case VK_RIGHT:
			cntrl->right();
			break;
		case 0x57: //W
			cntrl->WKey();
			break;
		case 0x41: //A
			cntrl->AKey();
			break;
		case 0x53: //S

			cntrl->SKey();
			break;
		case 0x44: //D
			cntrl->DKey();
			break;
		}

		break;
	case WM_HOTKEY:
		if (wParam == ID_HOTKEY) {
			SnakeWindowView::CenterWindow(hwnd);

		}
		break;

	case WM_CREATE:

		//STRG + C
		//MOD_CONTROL == strg,   0x43 == c
		//ID_HOTKEY ist die dieser Tastenkombination zugewiesene id, wird für Aufrufe benötigt
		RegisterHotKey(hwnd, ID_HOTKEY, MOD_CONTROL, 0x43);

		break;
	case WM_DESTROY:

		UnregisterHotKey(hwnd, ID_HOTKEY);
		//ohne die PostQuitMessage-Funktion wird das Fenster trotzdem durch das Kreuz geschlossen, aber das Programm läuft nicht weiter
		PostQuitMessage(0);
		break;
	}
	//default Window Procedure
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}



HWND* SnakeWindowView::initGrid()
{
	HWND* gridStart = new HWND[WIDTH*HEIGHT];

	RECT rc;
	GetClientRect(this->mainHandle, &rc);
	int i = 0;
	int lastLeft = 0;
	int lastUp = 0;

	int tileWidth = rc.right / this->WIDTH;
	int tileHeight = rc.bottom / this->HEIGHT;
	long index;
	for (int bottom = tileHeight; bottom <= rc.bottom; bottom += tileHeight) {
		for (int lastRight = tileWidth; lastRight <= rc.right; lastRight += tileWidth) {
			gridStart[i] = CreateWindowW(L"GridTileClass", NULL,
				WS_CHILD | WS_VISIBLE,
				lastLeft, lastUp, tileWidth, tileHeight,
				this->mainHandle, (HMENU)i, NULL, NULL);
			//speichere Information in dem Handle der Windows
			 index = GetWindowLongPtr(gridStart[i], GWLP_USERDATA);
			 index = i;
			 
			 SetWindowLongPtr(gridStart[i], GWLP_USERDATA, index);
			i++;
			lastLeft += tileWidth;
		}
		lastLeft = 0;
		lastUp += tileHeight;
	}
	
	RECT rc1, rc2;
	GetWindowRect(this->mainHandle, &rc1);
	GetClientRect(this->mainHandle, &rc2);

	int extratop = (rc1.bottom-rc2.bottom )- (rc1.top - rc2.top);
	

	SetWindowPos(this->mainHandle, NULL, 0, 0, tileWidth*(WIDTH), tileHeight*(HEIGHT)+extratop, NULL);
	GetWindowRect(this->mainHandle, &rc1);
	GetClientRect(this->mainHandle, &rc2);
	int extrawidth = (rc1.right - rc2.right) - (rc2.left - rc.left);
	SetWindowPos(this->mainHandle, NULL, 0, 0, tileWidth*(WIDTH)+extrawidth, tileHeight*(HEIGHT)+extratop, NULL);

	CenterWindow(this->mainHandle);

	return gridStart;
}


void SnakeWindowView::CenterWindow(HWND hwnd) {

	RECT rc = { 0 };
	GetWindowRect(hwnd, &rc);

	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;

	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w) / 2,
		(screen_h - win_h) / 2, 0, 0, SWP_NOSIZE);
}

void SnakeWindowView::RegisterGridClass(void) {

	HBRUSH hbrush = CreateSolidBrush(RGB(120, 120, 120));

	WNDCLASSW rwc = { 0 };

	rwc.lpszClassName = L"GridTileClass";
	rwc.hbrBackground = hbrush;
	rwc.lpfnWndProc = SnakeWindowView::GridTileProc;
	rwc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&rwc);
}



LRESULT CALLBACK SnakeWindowView::GridTileProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	static int val;
	static long index;
	static HPEN bkgrndPen = CreatePen(PS_SOLID, 10, RGB(120, 120, 120));
	static HBRUSH bkgrndBrush = CreateSolidBrush(RGB(120, 120, 120));
	static HPEN fruitPen = CreatePen(PS_SOLID, 10, RGB(249, 0, 0));
	static HBRUSH fruitBrush = CreateSolidBrush(RGB(249, 0, 0));

	static HPEN snakePen = CreatePen(PS_SOLID, 10, RGB(25, 25, 25));
	static HBRUSH snakeBrush = CreateSolidBrush(RGB(25, 25, 25));

	static HPEN headPen = CreatePen(PS_SOLID, 10, RGB(25, 180, 25));
	static HBRUSH headBrush = CreateSolidBrush(RGB(25, 180, 25));
	switch (msg) {

	case WM_UPDATEMESSAGE:

		break;
	case WM_ERASEBKGND:

			index = GetWindowLongPtr(hwnd, GWLP_USERDATA);
			

			HPEN* pen;
			HBRUSH*	brush;
			RECT rect;
			
			val = cntrl->model->field[index];

			switch (val) {
			case 0:
				pen = &bkgrndPen;
				brush = &bkgrndBrush;
				break;
			case -1:
				pen = &fruitPen;
				brush = &fruitBrush;
				break;
			default:
				if (index == cntrl->model->head) {
					pen = &headPen;
					brush = &headBrush;
				}
				else {
					pen = &snakePen;
					brush = &snakeBrush;
				}


				break;
			}

			//packe diese beiden in den device Context, sie werden smart hinzugefügt und von SelectObject richtig eingesetzt
			//wParam ist bei der WM_ERASEBKGND-Nachricht immer der device context, deshalb cast sicher
			SelectObject((HDC)wParam, *pen);
			SelectObject((HDC)wParam, *brush);
			//hole das innere (nicht Window) Rectangle und speicher in rect
			GetClientRect(hwnd, &rect);
			//zeichne ein neues
			Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
			
			return 0;
		

		break;
		
	default:

		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

