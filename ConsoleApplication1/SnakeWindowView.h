#pragma once
#include <Windows.h>

#pragma comment(lib, "user32.lib")

class SnakeWindowView
{
public:
	SnakeWindowView(int w, int h, HINSTANCE hInstance);
	~SnakeWindowView();
	int refreshIndex(int index);
private:
	int length;

	HINSTANCE hInstance;
	int WIDTH;
	int HEIGHT;


	void mainWindow();
	void grid();

};

