#pragma once
#include <Windows.h>
#include <stdio.h>
#include <sstream>
#pragma comment(lib, "user32.lib")


class SnakeController;

class SnakeWindowView
{
public:
	SnakeWindowView(int w, int h, HINSTANCE hInstance, SnakeController* controller);
	~SnakeWindowView();
	int refreshIndex(int index);
private:
	int length;

	HINSTANCE hInstance;


	int WIDTH;
	int HEIGHT;


	HWND mainHandle;
	HWND* grid;
	HWND mainWindow();
	HWND* initGrid();
	static void CenterWindow(HWND hwnd);

	void RegisterGridClass(void);

	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK GridTileProc(HWND hwnd, UINT msg,
		WPARAM wParam, LPARAM lParam);
};


