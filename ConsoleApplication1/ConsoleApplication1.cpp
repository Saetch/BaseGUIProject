// ConsoleApplication1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//
#pragma once

#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <sstream>
#include <Lmcons.h>
#include <VersionHelpers.h>
#include <time.h>
#include "SnakeController.h"
#include "SnakeWindowView.h"
//we can't add a SingleLinkedList.cpp file and include that, because a template can't be instantiated at compile time, so the compiler can't access the implementation
//anymore when creating an object
#include "SingleLinkedList_impl.h"

#pragma comment(lib, "user32.lib")
//HEAD
#define SHOW_UNNECESSARIES 0
#define SKIP_GAME 0
#define ID_HOTKEY 1


#define MENU_FILE_NEW 1
#define MENU_FILE_OPEN 2
#define MENU_FILE_QUIT 3

void AddMenus(HWND hwnd);
void showFirstBox();
int showSecondBoxDirectory();
int showThirdBoxMemory();
int showFourthBoxAndCheckListForFunctionality();


PWSTR byteConv(const std::string*  pstr);
PWSTR intConv(const std::string*  pstr);
PWSTR longConv(const std::string*  pstr);

PWSTR strToPWSTR(const char arr[], int len);
PWSTR strToPWSTR(const wchar_t arr[], int len);

//window procedure, to dispatch messsages to a window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam);
void CenterWindow(HWND hwnd);
LRESULT CALLBACK PanelProc(HWND, UINT, WPARAM, LPARAM);


void RegisterRedPanelClass(void);
void RegisterBluePanelClass(void);

HWND sub1, sub2;
BOOLEAN colorBool = false;
//ENDHEAD


/*
HINSTANCE --> Handle (typlose Referenz) auf ein Fenster
hPrevInstance ist immer NULL, Legacy-Referenz für 16 bit-Systeme
PWSTR --> Pointer to wide string | szCmdLine --> Konsolenparameter
CmdShow --> minimized, maximized, hidden 

int WINAPI wWinMain -> Diese main-function startet ohne ein kleines console-window, wie es bei int main() der Fall ist
die wWinMain function terminiert, wenn sie die WM_QUIT - Nachricht erhält


PS: für int WINAPI wWinMain bei Einstellungen->Settings->Linker->System->Subsystem nicht festgelegt einstellen, da ansonsten der Einstiegspunkt für spezialisierte, meist Konsolenanwendungen gewählt wird
*/
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow) {
	using std::string;
	using std::to_string;
	srand((unsigned int)time(0));


	//dumper für den ganzen kladdaradatsch, den man nicht brauch, aber gut zu sehen ist
	if (SHOW_UNNECESSARIES) {
		// +++++++++++++++++++++++++++++++++++++++++++++++++++ 1
		showFirstBox();
		// ++++++++++++++++++++++++++++++++++++++++++++++++++++ 2  derzeitiges
		showSecondBoxDirectory();
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++ 3  Speicherauslastung
		showThirdBoxMemory();
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++++ 4 eigene Listklasse benutzen/Testen
		showFourthBoxAndCheckListForFunctionality();
		printf_s("Debug here\n");
		//system("pause") ist kein netter system-call, aber funktioniert hier erstmal, um User nach input zu fragen, bis man fort fährt
		system("pause");
	}
	
	if (!SKIP_GAME) {
		//NUR IN DIESEM BONKER IST DER EIGENTLICHE CODE VOM EINSTIEGSPUNKT
		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		*/
		int width, height;
		printf_s("Länge (10-40): ");

		scanf_s("%d", &width);

		if (width < 10) width = 10;
		if (width > 40) width = 40;
		printf_s("Breite (10-30): ");

		scanf_s("%d", &height);
		if (height < 10) height = 10;
		if (height > 30) height = 30;
		SnakeController* ctrl = new SnakeController();

		Snakemodel* model = new Snakemodel(width, height);

		SnakeWindowView* view = new SnakeWindowView(width, height, hInstance, ctrl);

		ctrl->model = model;
		model->controller = ctrl;
		ctrl->view = view;
		ctrl->start();



		//while (model->getGameState()) {};

		//model->lost();

		//delete model;



		/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		*/
	}
	else {
		MSG  msg;
		WNDCLASSW wc = { 0 };
		wc.lpszClassName = L"Simple menu";
		wc.hInstance = hInstance;
		wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		wc.lpfnWndProc = WndProc;
		wc.hCursor = LoadCursor(0, IDC_ARROW);

		RegisterClassW(&wc);
		CreateWindowW(wc.lpszClassName, L"Simple menu",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			100, 100, 350, 250, 0, 0, hInstance, 0);

		while (GetMessage(&msg, NULL, 0, 0)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}






	return 0;
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_CREATE:

		AddMenus(hwnd);
		break;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {

		case MENU_FILE_NEW:
		case MENU_FILE_OPEN:

			MessageBeep(MB_ICONINFORMATION);
			break;

		case MENU_FILE_QUIT:

			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void AddMenus(HWND hwnd) {

	HMENU hMenubar;
	HMENU hMenu;

	hMenubar = CreateMenu();
	hMenu = CreateMenu();

	AppendMenuW(hMenu, MF_STRING, MENU_FILE_NEW, L"&New");
	AppendMenuW(hMenu, MF_STRING, MENU_FILE_OPEN, L"&Open");
	AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenu, MF_STRING, MENU_FILE_QUIT, L"&Quit"); //je ein Eintrag nach dem dropdown von file --> new -> Open -> - -> Quit
	
	AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"&File"); //eine Zeile, für drop-down (POPUP)
	SetMenu(hwnd, hMenubar);
}


LRESULT CALLBACK PanelProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {
	static COLORREF backcolor = RGB(0, 255, 0);
	switch (msg) {
	case WM_ERASEBKGND:
		if (hwnd == sub1 && colorBool) {
			HPEN pen;
			HBRUSH	brush;
			RECT rect;
			//PEN ist für den Rand da. Hat immer mindestens Größe 1, deshalb zu passender Farbe
			pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			//BRUSH ist die Farbe des Vierecks
			brush = CreateSolidBrush(RGB(0, 255, 0));
			//packe diese beiden in den device Context, sie werden smart hinzugefügt und von SelectObject richtig eingesetzt
			//wParam ist bei der WM_ERASEBKGND-Nachricht immer der device context, deshalb cast sicher
			SelectObject((HDC)wParam, pen);
			SelectObject((HDC)wParam, brush);
			//hole das innere (nicht Window) Rectangle und speicher in rect
			GetClientRect(hwnd, &rect);
			//zeichne ein neues
			Rectangle((HDC)wParam, rect.left, rect.top, rect.right, rect.bottom);
			
			return (INT_PTR)brush;
		}

		break;
	case WM_LBUTTONUP:
		
		
		MessageBeep(MB_OK);
		if (hwnd == sub1) {
			colorBool = true;
			SendMessage(sub1, WM_ERASEBKGND, (UINT_PTR)GetWindowDC(sub1), 0);
		}
		
		break;

	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void CenterWindow(HWND hwnd) {

	RECT rc = { 0 };
	GetWindowRect(hwnd, &rc);

	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;

	int screen_w = GetSystemMetrics(SM_CXSCREEN);
	int screen_h = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(hwnd, HWND_TOP, (screen_w - win_w) / 2,
		(screen_h - win_h) / 2, 0, 0, SWP_NOSIZE);
}


void RegisterRedPanelClass(void) {

	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));

	WNDCLASSW rwc = { 0 };

	rwc.lpszClassName = L"RedPanelClass";
	rwc.hbrBackground = hbrush;
	rwc.lpfnWndProc = PanelProc;
	rwc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&rwc);
}

void RegisterBluePanelClass(void) {

	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));

	WNDCLASSW rwc = { 0 };

	rwc.lpszClassName = L"BluePanelClass";
	rwc.hbrBackground = hbrush;
	rwc.lpfnWndProc = PanelProc;
	rwc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&rwc);
}

// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.


void showFirstBox() {
	using std::to_string;
	using std::string;
	using std::stringstream;

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	stringstream sstream;
	sstream << "The screen size is: " << to_string(x) << " x " << y;
	string str = sstream.str();
	PWSTR pntr_wchar = byteConv(&str);
	//Nachrichtenbox pausiert programmausführung bis Fenster geschlossen
	// NULL --> bezieht sich nicht auf ein vorhandenes Fenster, ansonsten hier HINSTANCE einfügen
	// pntr_wchar --> Text
	// L"Title" --> Title
	MessageBoxW(NULL, pntr_wchar, L"Title", MB_OK);

	free(pntr_wchar);
}


int  showSecondBoxDirectory() {
	wchar_t buf[MAX_PATH + 1];
	int r = GetCurrentDirectory(MAX_PATH + 1, buf);
	if (r == 0) return 1;
	PWSTR pntr2 = strToPWSTR(buf, sizeof(buf));
	r = MessageBoxW(NULL, pntr2, L"CURRENT DIRECTORY:", MB_OK);
	if (r == 0) return 1;

	free(pntr2);
	return 0;
}

int showThirdBoxMemory() {
	int r;
	std::string str;
	std::stringstream sstream;
	//initialisiere array mit 0 -->  BSP: 	int arr[50] = { 0 };

	MEMORYSTATUSEX mem = { 0 };

	//pass own length (like array-length) to the structure, to keep it stored. Results in no int len variable being passed to GlobalMemoryStatusEx
	mem.dwLength = sizeof(mem);

	//store current memory information in the mem structure
	r = GlobalMemoryStatusEx(&mem);
	sstream.str("");
	//clear only clears flags, etc. Should be called, when initializing the sstream anew
	sstream.clear();
	sstream << "Memory in use: " << mem.dwMemoryLoad << "percent\n"
		<< "Total physical memory: " << mem.ullTotalPhys << "\n"
		<< "Total free physical memory: " << mem.ullAvailPhys << "\n"
		<< "Total virtual memory: " << mem.ullAvailVirtual << "\n"
		<< "Free virtual memory: " << mem.ullAvailVirtual << "\n";
	str = sstream.str();
	PWSTR pntr3 = intConv(&str);

	r = MessageBoxW(NULL, pntr3, L"Memory Usage:", MB_OK);
	if (r == 0) return 1;

	free(pntr3);
	return 0;
}


int showFourthBoxAndCheckListForFunctionality(){
	//check debugger for memory leaks, just fill with bunch of stuff, delete and repeat, also check GetTickCount for speed performance
	SingleLinkedList<int>* list = new SingleLinkedList<int>();
	DWORD start;
	DWORD end;
	DWORD res;
	int result[1000] = { 0 };

	for (int c = 0; c < 500; c++) {
		start = GetTickCount();
		for (int i = 0; i < 10000; i = i + 2) {
			int* elem = new int(rand());
			list->pushBack(elem);
		}

		while (list->getSize() > 0) {
			list->removeAndFreeElem(0);
		}
		end = GetTickCount();
		res = end - start;
		for (int j = 0; j < 1000; j++) {
			if (j == res) {
				result[j]++;
				break;
			}
		}
	}

	for (int i = 0; i < 1000; i++) {
		if (result[i] != 0) {
			printf_s("%d -> %d\n", i, result[i]);
		}
	}


	//fülle mit ein paar Daten, die man anzeigen lassen kann
	for (int i = 0; i < 50; i = i++) {
		int* elem = new int(rand() % 100);
		list->pushBack(elem);
	}


	//zeige Liste
	std::string str = list->to_string();
	PWSTR pntr4 = intConv(&str);
	int r = MessageBoxW(NULL, pntr4, L"List: ", MB_OK);

	//und löschen
	while (list->getSize() > 0) {
		list->removeAndFreeElem(0);
	}

	if (r == 0) return 1;
	return 0;
}


PWSTR byteConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	PWSTR outp = (PWSTR)calloc((*pstr).length() + 1, sizeof(WCHAR));
	for (BYTE i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR intConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)calloc(pstr->length() + 1, sizeof(WCHAR));
	for (unsigned int i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR longConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)calloc(pstr->length() + 1, sizeof(WCHAR));
	for (unsigned long i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR strToPWSTR(const char arr[], int len) {
	WCHAR* ret = (WCHAR*)calloc(len, sizeof(WCHAR));
	for (unsigned int i = 0; i < (unsigned int)len; i++) {
		ret[i] = arr[i];
	}
	return ret;
}

PWSTR strToPWSTR(const wchar_t arr[], int len) {
	WCHAR* ret = (WCHAR*)calloc(len, sizeof(WCHAR));
	for (unsigned int i = 0; i < (unsigned int)len; i++) {
		ret[i] = arr[i];
	}
	return ret;
}