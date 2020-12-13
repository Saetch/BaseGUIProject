#pragma once
#include <time.h>
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include "SingleLinkedList_impl.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <sstream>
#include <mutex>


class SnakeController;

class Snakemodel
{
public:
	int head;

	int* field;
	BYTE direction;
	SnakeController* controller;
	int inline headVal();

	SingleLinkedList<int>* body;

	int(*fnct)(int width, int height);


	//anstatt, dass wir einen gesamten Canvas neuzeichnen bei jedem update-Tick, können wir gezielt angeben, welche Felder geändert wurden und nur für diese eine
	//update Message-senden
	int returnChanged(int arr[], int len);


	void start();

	BYTE turnUP();
	BYTE turnDown();
	BYTE turnLeft();
	BYTE turnRight();
	void pause();
	void restart();

	Snakemodel(int width, int height);
	~Snakemodel();

	inline int getGameState() {
		return this->gameState.load();
	}
	inline int getSpeed() {
		return this->speed;
	};
	inline int setSpeed(int newSpeed) {
		return this->speed = newSpeed;
	};
	inline int lost() {
		this->gameState.store(0);
		if (thr1 != NULL) thr1->join();
		return 0;
	};

	int reduceOne(int* i);
private:
	int WIDTH;
	int HEIGHT;
	int speed;
	int length;
	int nextStep;
	std::atomic<BYTE> gameState;
	int generateNewFood();
	int game();
	std::atomic<BYTE> illegalDirection;
	int step();
	std::thread* thr1;
	std::mutex dirMutex;
	int crawlOne(ListElem<int>** listElem);
	void printField();
};