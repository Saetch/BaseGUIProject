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

std::mutex mutex;


int Snakemodel::returnChanged(int arr[], int len)
{

	
	return 0;
}

void Snakemodel::start()
{
	printf_s("Starting game session ...\n");
	this->gameState.store(SNAKE_GAMESTATE_RUNNING);
	//memberfunktionen brauchen nicht nur die Funktion, sondern auch die zugehörige Instanz
	thr1 = new std::thread(&Snakemodel::game, &(*this));
	
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
	this->WIDTH = width;
	this->HEIGHT = height;
	this->body = new SingleLinkedList<int>();
	
	// this ist in C++ ein Pointer 
	(*		this).length = width * height;
	(*		this).direction = SNAKE_RIGHT;
	this->illegalDirection.store ( SNAKE_LEFT );
	this->field = (int*)calloc(this->length, sizeof(int));

	//wieviele millisekunden vergehen, bis die Bewegung weiterläuft
	this->speed = 1000;
	
	//this might be unneeded
	this->nextStep = NULL;
	this->body = new SingleLinkedList<int>();
	for (int i = 0; i < DEFAULTLENGTH;  ) {
		this->body->addBack(i);
		this->field[i] = ++i;
	}
	
}

Snakemodel::~Snakemodel()
{ 
	
	
	while (this->body->getSize() > 0) {
		this->body->removeAndFreeElem(0);
	}
	free(this->field);

	this->gameState.store( SNAKE_GAMESTATE_LOST );
	

	
	delete this->body;
	
	
}



int Snakemodel::eat()
{
	return 0;
}

int Snakemodel::generateNewFood()
{
	return 0;
}

int Snakemodel::game()
{
    //printf_s("HELLO, THREAD STARTED\n");

	auto callMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

	callMs = callMs + (std::chrono::milliseconds)this->speed;



	int i = 0;


	//PS: bei jedem Datentyp über nano kommt es erst bei über 500 Jahren zu einem Overflow
	while (this->gameState.load() ) {

		if (i >= 20) {
			this->gameState.store(SNAKE_GAMESTATE_LOST);
		}

		printf_s("%d\n\n", i++);
		printf_s(this->body->to_string().c_str());
		printf_s("\n");

		//wir rechnen immer die Zeit zwischen aufrufen dazu, damit es nicht zu einer Zeitverschiebung wegen den ausgeführten Befehlen kommt
		callMs += (std::chrono::milliseconds)this->speed;

		std::this_thread::sleep_until(callMs);
		
		this->step();
		
	}



	return 0;

}


int Snakemodel::reduceOne(int* i) {
	
	(*i)--;
	return 0;
}

int Snakemodel::step()
{

	//TODO remove this line
	if (this->body->getSize() == 0) return 0;
	static ListElem<int>** listElem = this->body->getElemP();  //Pointer to pointer, so it never changes
	printf_s("Element: %d\n", this->field[*(*listElem)->element]);
	ListElem<int>* curr = *listElem; //firstElement
	for (int i = 0; i < this->body->getSize(); i++) {
		this->field[*(curr->element)]--;
		curr = curr->next;
	}
	if (this->field[*(*listElem)->element] <= 0) {
		this->body->removeAndFreeElem(0);
	}







	


	return 0;
}
