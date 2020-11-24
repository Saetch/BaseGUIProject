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

#pragma comment(lib, "user32.lib")

PWSTR byteConv(const std::string*  pstr);
PWSTR intConv(const std::string*  pstr);
PWSTR longConv(const std::string*  pstr);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR szCmdLine, int CmdShow) {
	using std::string;
	using std::to_string;


	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	std::stringstream sstream;
	sstream << "The screen size is: " << to_string(x) << " x " << y << " MAXBYTE: "<< MAXBYTE;
	string str = sstream.str();

	PWSTR pntr_wchar = byteConv(&str);
	MessageBoxW(NULL, pntr_wchar , L"Title", MB_OK);

	free(pntr_wchar);
	return 0;
}

PWSTR byteConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*) malloc(sizeof(WCHAR)* (*pstr).length());
	for (BYTE i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR intConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)malloc(sizeof(WCHAR)*MAXBYTE);
	for (unsigned int i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
}

PWSTR longConv(const std::string*  pstr) {
	const char* c_str = (*pstr).c_str();
	WCHAR* outp = (WCHAR*)malloc(sizeof(WCHAR)*MAXBYTE);
	for (unsigned long i = 0; i <= pstr->length() && i < MAXBYTE; i++) {
		outp[i] = c_str[i];
	}
	return outp;
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
