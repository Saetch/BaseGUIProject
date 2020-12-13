#pragma once
#include "SnakeWindowView.h"
#include "Snakemodel.h"
class SnakeController
{
public:
	SnakeController(int w, int h);
	~SnakeController();
	Snakemodel* model;
	SnakeWindowView* view;

	int refreshIndex(int index);
	void initModel();

	int start();

	void WKey();
	void AKey();
	void SKey();
	void DKey();
	void esc();
	void spaceBar();
private: 
	int WIDTH;
	int HEIGHT;
};