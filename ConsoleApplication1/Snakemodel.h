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

class Snakemodel
{
public:	
	int* field;
	BYTE direction;
	

	SingleLinkedList<int>* body;

	int(* fnct)(int width, int height);


		//anstatt, dass wir einen gesamten Canvas neuzeichnen bei jedem update-Tick, können wir gezielt angeben, welche Felder geändert wurden und nur für diese eine
		//update Message-senden
		int returnChanged(int arr[], int len);


		void start();

		BYTE turnR();
		BYTE turnL();

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
		inline int lost(){
			if (thr1 != NULL) thr1->join();
			this->gameState.store(0);
			return 0;
		};

		int reduceOne(int* i);
private:
	int WIDTH;
	int HEIGHT;
	int speed;
	int length;
	int head;
	int nextStep;
	std::atomic<BYTE> gameState;
	int eat();
	int generateNewFood();
	int game();
	std::atomic<BYTE> illegalDirection;
	int step();
	std::thread* thr1;
};

