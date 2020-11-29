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

#pragma comment(lib, "user32.lib")




PWSTR byteConv(const std::string*  pstr);
PWSTR intConv(const std::string*  pstr);
PWSTR longConv(const std::string*  pstr);

PWSTR strToPWSTR(const char arr[], int len);
PWSTR strToPWSTR(const wchar_t arr[], int len);
/*
HINSTANCE --> Handle (typlose Referenz) auf ein Fenster
PWSTR --> Pointer to wide string | szCmdLine --> Konsolenparameter
CmdShow --> bool 

Diese main-function startet ohne ein kleines console-window, wie es bei int main(void) der Fall wäre
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow) {
	using std::string;
	using std::to_string;


	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	std::stringstream sstream;

	wchar_t buf[MAX_PATH+1];
	int r = GetCurrentDirectory(MAX_PATH + 1, buf);

	MessageBoxW(NULL, strToPWSTR(buf, sizeof(buf)), strToPWSTR("CURRENT DIRECTORY:",19), MB_OK);

	sstream << "The screen size is: " << to_string(x) << " x " << y << " USERNAME: ";
	string str = sstream.str();
	PWSTR pntr_wchar = byteConv(&str);
	//Nachrichtenbox pausiert programmausführung bis Fenster geschlossen
	// NULL --> bezieht sich nicht auf ein vorhandenes Fenster, ansonsten hier HINSTANCE einfügen
	// pntr_wchar --> Text
	// L"Title" --> Title
	MessageBoxW(NULL, pntr_wchar , L"Title", MB_OK);

	free(pntr_wchar);

	return 0;
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




// Programm ausführen: STRG+F5 oder "Debuggen" > Menü "Ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
