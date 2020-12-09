#include "SnakeWindowView.h"

SnakeWindowView::SnakeWindowView(int w, int h, HINSTANCE hInstance)
{
	WIDTH = w;
	HEIGHT = h;

	this->length = w * h;
	this->hInstance = hInstance;

	mainWindow();

}

SnakeWindowView::~SnakeWindowView()
{
}

int SnakeWindowView::refreshIndex(int index)
{
	return 0;
}

void SnakeWindowView::mainWindow()
{
	//variable, um Nachrichten zu holen
	MSG  msg;
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
	wc.lpfnWndProc = WndProc;
	//Mauszeiger auf default
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//Fenster Icon default
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//Fenster registrieren, damit das OS damit kommunizieren und es anzeigen kann
	RegisterClassW(&wc);
	//Fenster erstellen mit Werten: wc.lpszClassName sorgt dafür, dass unsere Fenster-Vorlage benutzt wird, Referenz auf dieses Fenster
	//wird dann in hwnd gespeichert (handle)
	hwnd = CreateWindowW(wc.lpszClassName, L"Windows",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 250, 180, 0, 0, hInstance, NULL);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_KEYDOWN:

		if (wParam == VK_ESCAPE) {

			int ret = MessageBoxW(hwnd, L"Are you sure to quit?",
				L"Message", MB_OKCANCEL);

			if (ret == IDOK) {

				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}
		}

		if (wParam == 0x46) //F
		{

		}

		break;
/*	case WM_HOTKEY:
		if (wParam == ID_HOTKEY) {
			CenterWindow(hwnd);

		}
		break;*/

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

void SnakeWindowView::grid()
{

}
