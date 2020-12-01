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

#include "SingleLinkedList.h"
//we can't add a SingleLinkedList.cpp file and include that, because a template can't be instantiated at compile time, so the compiler can't access the implementation
//anymore when creating an object
#include "SingleLinkedList_impl.h"

#pragma comment(lib, "user32.lib")


//HEAD

PWSTR byteConv(const std::string*  pstr);
PWSTR intConv(const std::string*  pstr);
PWSTR longConv(const std::string*  pstr);

PWSTR strToPWSTR(const char arr[], int len);
PWSTR strToPWSTR(const wchar_t arr[], int len);

//window procedure, to dispatch messsages to a window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam);
//ENDHEAD


/*
HINSTANCE --> Handle (typlose Referenz) auf ein Fenster
hPrevInstance ist immer NULL, Legacy-Referenz für 16 bit-Systeme
PWSTR --> Pointer to wide string | szCmdLine --> Konsolenparameter
CmdShow --> minimized, maximized, hidden 

int WINAPI wWinMain -> Diese main-function startet ohne ein kleines console-window, wie es bei int main() der Fall ist
die wWinMain function terminiert, wenn sie die WM_QUIT - Nachricht erhält
*/
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow) {
	using std::string;
	using std::to_string;
	srand((unsigned int)time(0));


	// +++++++++++++++++++++++++++++++++++++++++++++++++++ 1
	

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	std::stringstream sstream;
	sstream << "The screen size is: " << to_string(x) << " x " << y;
	string str = sstream.str();
	PWSTR pntr_wchar = byteConv(&str);
	//Nachrichtenbox pausiert programmausführung bis Fenster geschlossen
	// NULL --> bezieht sich nicht auf ein vorhandenes Fenster, ansonsten hier HINSTANCE einfügen
	// pntr_wchar --> Text
	// L"Title" --> Title
	MessageBoxW(NULL, pntr_wchar, L"Title", MB_OK);

	free(pntr_wchar);


	// ++++++++++++++++++++++++++++++++++++++++++++++++++++ 2  derzeitiges


	wchar_t buf[MAX_PATH+1];
	int r = GetCurrentDirectory(MAX_PATH + 1, buf);
	if (r == 0) return 1;
	PWSTR pntr2 = strToPWSTR(buf, sizeof(buf));
	r = MessageBoxW(NULL, pntr2 , L"CURRENT DIRECTORY:", MB_OK);
	if (r == 0) return 1;

	free(pntr2);
	

	// +++++++++++++++++++++++++++++++++++++++++++++++++++++ 3  Speicherauslastung


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


	// +++++++++++++++++++++++++++++++++++++++++++++++++++++++ 4 eigene Listklasse benutzen/Testen


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
	for (int i = 0; i < 50; i = i ++ ) {
		int* elem = new int(rand()%100);
		list->pushBack(elem);
	}


	//zeige Liste
	str = list->to_string();
	PWSTR pntr4 = intConv(&str);
	r = MessageBoxW(NULL, pntr4, L"List: ", MB_OK);

	//und löschen
	while (list->getSize() > 0) {
		list->removeAndFreeElem(0);
	}

	if (r == 0) return 1;



	

	printf_s("Debug here\n");
	//system("pause") ist kein netter system-call, aber funktioniert hier erstmal, um User nach input zu fragen, bis man fort fährt
	system("pause");
	
	//++++++++++++++++++++++++++++++++++++++++++++++++  5  NEUES FENSTER


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
	hwnd = CreateWindowW(wc.lpszClassName, L"Window",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		100, 100, 350, 250, NULL, NULL, hInstance, NULL);
	//Fenster zeigen
	ShowWindow(hwnd, CmdShow);
	UpdateWindow(hwnd);

	//hole Nachricht für das Fenster aus dem Message-Buffer
	while (GetMessage(&msg, NULL, 0, 0)) {

		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

PWSTR byteConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	PWSTR outp = (PWSTR) calloc( (*pstr).length()+1, sizeof(WCHAR));
	for (BYTE i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR intConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)calloc( pstr->length()+1, sizeof(WCHAR));
	for (unsigned int i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR longConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)calloc(pstr->length()+1, sizeof(WCHAR));
	for (unsigned long i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR strToPWSTR(const char arr[], int len) {
	WCHAR* ret = (WCHAR*)calloc(len , sizeof(WCHAR));
	for (unsigned int i = 0; i < (unsigned int) len; i++) {
		ret[i] = arr[i];
	}
	return ret;
}

PWSTR strToPWSTR(const wchar_t arr[], int len) {
	WCHAR* ret = (WCHAR*)calloc(len, sizeof(WCHAR));
	for (unsigned int i = 0; i < (unsigned int) len; i++) {
		ret[i] = arr[i];
	}
	return ret;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
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
