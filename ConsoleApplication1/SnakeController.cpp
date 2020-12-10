#include "SnakeController.h"

SnakeController::SnakeController()
{
}

SnakeController::~SnakeController()
{
}

int SnakeController::refreshIndex(int index)
{
	this->view->refreshIndex(index);
	return 0;
}


void SnakeController::initModel()
{

	//this->model->controller = this;
}

int SnakeController::start()
{
	if (this->model == NULL || this->view == NULL) {
		return 1;
	}
	this->model->start();
	MSG  msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}



void SnakeController::WKey()
{
	this->model->turnUP();
}

void SnakeController::AKey()
{
	this->model->turnLeft();
}

void SnakeController::SKey()
{
	this->model->turnDown();
}

void SnakeController::DKey()
{
	this->model->turnRight();
}

void SnakeController::spaceBar()
{
	this->model->pause();
}
