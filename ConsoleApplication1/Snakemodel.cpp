#include "Snakemodel.h"


#define SNAKE_UP 0
#define SNAKE_RIGHT 1
#define SNAKE_DOWN 2
#define SNAKE_LEFT 3

#define SNAKE_GAMESTATE_RUNNING 1
#define SNAKE_GAMESTATE_PAUSED 2
#define SNAKE_GAMESTATE_LOST 0

#define MULTIPLIER 1

#define DEFAULTLENGTH 3

int Snakemodel::returnChanged(int arr[], int len)
{

	
	return 0;
}

void Snakemodel::start()
{
	//memberfunktionen brauchen nicht nur die Funktion, sondern auch die zugehörige Instanz
	thr1 = std::thread(&Snakemodel::step, &(*this));
	this->gameState = SNAKE_GAMESTATE_RUNNING;
}

BYTE Snakemodel::turnR()
{
	return 0;
}

BYTE Snakemodel::turnL()
{
	return 0;
}

void Snakemodel::pause()
{
}

void Snakemodel::restart()
{
}


Snakemodel::Snakemodel(int width, int height)
{
	// this ist in C++ ein Pointer 
	(*		this).length = width * height;
	(*		this).direction = SNAKE_RIGHT;
	this->illegalDirection = SNAKE_LEFT;
	this->field = (int*)calloc(this->length, sizeof(int));

	//wieviele millisekunden vergehen, bis die Bewegung weiterläuft
	this->speed = 1000;
	
	//this might be unneeded
	this->nextStep = NULL;

	for (int i = 0; i < DEFAULTLENGTH; ) {
		this->body.pushBack(this->field+i);
		this->field[i] = ++i;
	}
}

Snakemodel::~Snakemodel()
{
	free(this->field);
	while (this->body.getSize() > 0) {
		this->body.removeElement(0);
	}
}



int Snakemodel::eat()
{
	return 0;
}

int Snakemodel::generateNewFood()
{
	return 0;
}

int Snakemodel::step()
{
	auto callMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

	callMs = callMs + (std::chrono::milliseconds)this->speed;



	int i = 0;


	//PS: bei jedem Datentyp über nano kommt es erst bei über 500 Jahren zu einem Overflow
	while (this->gameState ) {
	
		printf_s("%d\n", i++);
		printf_s("%d\n\n", (int)callMs.time_since_epoch().count());

		//wir rechnen immer die Zeit zwischen aufrufen dazu, damit es nicht zu einer Zeitverschiebung wegen den ausgeführten Befehlen kommt
		callMs += (std::chrono::milliseconds)this->speed;

		std::this_thread::sleep_until(callMs);
		

		
	}



	return 0;

}
