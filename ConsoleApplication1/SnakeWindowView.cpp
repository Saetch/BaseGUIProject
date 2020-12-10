#include "SnakeWindowView.h"
#include "SnakeController.h"


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
}


SnakeWindowView::~SnakeWindowView()
{

	delete this->grid;
}


int SnakeWindowView::refreshIndex(int index)
{
	SendMessage(this->grid[index],WM_ERASEBKGND, (UINT_PTR)GetWindowDC(this->grid[index]), NULL);
	return 0;
}

HWND SnakeWindowView::mainWindow()
{
	//handle zum Fenster, das wir �ffnen wollen
	HWND hwnd;
	//Fenster-Klasse. Hier kommt Konfiguration rein, damit windows wei�, wie wir das Fenster haben wollen
	//davon k�nnen mehrere erstellt werden. Es ist NICHT ein Fenster, es ist die Vorlage f�r ein Fenster
	WNDCLASSW wc;
	//zeichne neu, wenn bewegt oder ver�ndert
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//Unterklassen-Values
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	//Name
	wc.lpszClassName = L"Window";
	//handle-Instanz, aus main
	wc.hInstance = hInstance;
	//Hintergrund-F�rben
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	//kein Men�
	wc.lpszMenuName = NULL;
	//function-pointer f�r message-callback procedure = unsere unten definierte Function
	wc.lpfnWndProc = SnakeWindowView::MainWndProc;
	//Mauszeiger auf default
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Fenster Icon default
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//Fenster registrieren, damit das OS damit kommunizieren und es anzeigen kann
	RegisterClassW(&wc);
	//Fenster erstellen mit Werten: wc.lpszClassName sorgt daf�r, dass unsere Fenster-Vorlage benutzt wird, Referenz auf dieses Fenster
	//wird dann in hwnd gespeichert (handle)
	hwnd = CreateWindowW(wc.lpszClassName, L"Windows",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, this->WIDTH*FIELDPIXELMOD, this->HEIGHT*FIELDPIXELMOD, 0, 0, hInstance, NULL);

	return hwnd;
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

				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}
			break;
		case 0x46: 
			//PAUSE -> F-key
			break;

		case 0x57: //W
			cntrl->WKey();
			printf_s("W");
			break;
		case 0x41: //A
			cntrl->AKey();
			printf_s("A");
			break;
		case 0x53: //S
			cntrl->SKey();
			printf_s("S");
			break;
		case 0x44: //D
			cntrl->DKey();
			printf_s("D");
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
		//ID_HOTKEY ist die dieser Tastenkombination zugewiesene id, wird f�r Aufrufe ben�tigt
		RegisterHotKey(hwnd, ID_HOTKEY, MOD_CONTROL, 0x43);

		break;
	case WM_DESTROY:

		UnregisterHotKey(hwnd, ID_HOTKEY);
		//ohne die PostQuitMessage-Funktion wird das Fenster trotzdem durch das Kreuz geschlossen, aber das Programm l�uft nicht weiter
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
			 index = GetWindowLongPtr(gridStart[i], GWL_USERDATA);
			 index = i;
			 SetWindowLongPtr(gridStart[i], GWL_USERDATA, index);
			i++;
			lastLeft += tileWidth;
		}
		lastLeft = 0;
		lastUp += tileHeight;
	}
	
	SetWindowPos(this->mainHandle, NULL, 100, 100, tileWidth*WIDTH, tileHeight*HEIGHT, NULL);
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
	switch (msg) {

	case WM_UPDATEMESSAGE:

		break;
	case WM_ERASEBKGND:
		 

			index = GetWindowLongPtr(hwnd, GWL_USERDATA);


			HPEN pen;
			HBRUSH	brush;
			RECT rect;
			
			val = cntrl->model->field[index];

			switch (val) {
			case 0:
				pen = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
				brush = CreateSolidBrush(RGB(120, 120, 120));
				break;
			case -1:
				pen = CreatePen(PS_SOLID, 1, RGB(249, 0, 0));
				brush = CreateSolidBrush(RGB(230, 0, 0));
				break;
			default:
				pen = CreatePen(PS_SOLID, 1, RGB(25, 25, 25));
				brush = CreateSolidBrush(RGB(25, 25, 25));
				break;
			}

			//packe diese beiden in den device Context, sie werden smart hinzugef�gt und von SelectObject richtig eingesetzt
			//wParam ist bei der WM_ERASEBKGND-Nachricht immer der device context, deshalb cast sicher
			SelectObject((HDC)wParam, pen);
			SelectObject((HDC)wParam, brush);
			//hole das innere (nicht Window) Rectangle und speicher in rect
			GetClientRect(hwnd, &rect);
			//zeichne ein neues
			Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);

			return (INT_PTR)brush;
		

		break;

	default:

		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

