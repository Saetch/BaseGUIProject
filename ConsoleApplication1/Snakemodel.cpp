#include "Snakemodel.h"
#include "SnakeController.h"

#define SNAKE_UP 0
#define SNAKE_RIGHT 1
#define SNAKE_DOWN 2
#define SNAKE_LEFT 3

#define SNAKE_GROWTH_PER_FRUIT 2
#define SNAKE_DEFAULTSPEED 80
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
	//memberfunktionen brauchen nicht nur die Funktion, sondern auch die zugeh�rige Instanz
	thr1 = new std::thread(&Snakemodel::game, &(*this));

}

BYTE Snakemodel::turnUP()
{
	if (this->illegalDirection == SNAKE_UP) return 1;
	dirMutex.lock();
	this->direction = SNAKE_UP;
	dirMutex.unlock();
	return 0;
}

BYTE Snakemodel::turnDown()
{
	if (this->illegalDirection == SNAKE_DOWN) return 1;
	dirMutex.lock();
	this->direction = SNAKE_DOWN;
	dirMutex.unlock();
	return 0;
}

BYTE Snakemodel::turnLeft()
{
	if (this->illegalDirection == SNAKE_LEFT) return 1;
	dirMutex.lock();
	this->direction = SNAKE_LEFT;
	dirMutex.unlock();
	return 0;
}

BYTE Snakemodel::turnRight()
{
	if (this->illegalDirection == SNAKE_RIGHT) return 1;
	dirMutex.lock();
	this->direction = SNAKE_RIGHT;
	dirMutex.unlock();
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

	if (width <= 0 || height <= 0) {
		throw _CRT_ERROR;
	}

	this->WIDTH = width;
	this->HEIGHT = height;
	this->body = new SingleLinkedList<int>();

	// this ist in C++ ein Pointer 
	(*this).length = width * height;
	(*this).direction = SNAKE_RIGHT;
	this->illegalDirection.store(SNAKE_LEFT);
	this->field = (int*)calloc(this->length, sizeof(int));

	//wieviele millisekunden vergehen, bis die Bewegung weiterl�uft
	this->speed = SNAKE_DEFAULTSPEED;

	//this might be unneeded
	this->nextStep = NULL;
	this->body = new SingleLinkedList<int>();
	for (int i = 0; i < DEFAULTLENGTH; i++) {
		this->body->addBack(i);
		this->field[i] = i + 1;
	}
	this->generateNewFood();

}

Snakemodel::~Snakemodel()
{
	this->lost();

	while (this->body->getSize() > 0) {
		this->body->removeAndFreeElem(0);
	}
	free(this->field);




	delete this->body;
	

}

void Snakemodel::changeDirLeft()
{
	dirMutex.lock();
	this->direction = (this->direction+3)%4;
	dirMutex.unlock();
}

void Snakemodel::changeDirRight()
{
	dirMutex.lock();
	this->direction = (this->direction+1)%4;
	dirMutex.unlock();
}




int Snakemodel::generateNewFood()
{
	int i = 0;
	int newIndex = rand() % this->length;
	while (this->field[newIndex] != 0 && i < 1000) {
		newIndex = rand() % this->length;
		i++;
	}
	this->field[newIndex] = -1;
	if (i == 1000) {
		printf_s("Generate function goofed ... !\n");
		return -1;
	}
	return newIndex;
}

int Snakemodel::game()
{
	printf_s("HELLO, THREAD STARTED\n");

	auto callMs = (std::chrono::time_point_cast<std::chrono::milliseconds>)(std::chrono::steady_clock::now());

	callMs = callMs + (std::chrono::milliseconds)this->speed;





	//PS: bei jedem Datentyp �ber nano kommt es erst bei �ber 500 Jahren zu einem Overflow
	while (this->gameState.load()) {
		this->step();

		//wir rechnen immer die Zeit zwischen aufrufen dazu, damit es nicht zu einer Zeitverschiebung wegen den ausgef�hrten Befehlen kommt
		callMs += (std::chrono::milliseconds)this->speed;
		std::this_thread::sleep_until(callMs);
	
	}

	std::cout << "THREAD ENDED" << std::endl;
	return 0;

}


int Snakemodel::reduceOne(int* i) {

	(*i)--;
	return 0;
}



int Snakemodel::step()
{
	int ret;

	if (this->body->getSize() == 0) return 0;


	ListElem<int>** listElem = this->body->getElemP();  //Pointer to pointer, so it never changes
	ListElem<int>* curr = *listElem; //firstElement
	if (listElem == NULL) {
		listElem = this->body->getElemP();
		curr = *listElem;
	}
	for (int i = 0; i < this->body->getSize(); i++) {
		this->field[*(curr->element)]--;
		curr = curr->next;
	}
	this->crawlOne(listElem);
	int ind = *(*listElem)->element;
	ret = this->field[ind];
	if (this->body->get(0) == this->head) {
		std::cout << "OOOF!";
		this->body->removeAndFreeElem(0);
		controller->refreshIndex(ind);
	}
	if (ret <= 0) {
		controller->refreshIndex(ind);
		this->body->removeAndFreeElem(0);
	}







	return 0;
}

int Snakemodel::headVal()
{
	return this->field[this->head];
}

int Snakemodel::crawlOne(ListElem<int>** listElem)
{
	const int index = this->body->getLast();
	int newIndex;
	dirMutex.lock();
	switch (direction) {
	case SNAKE_RIGHT:
		newIndex = index + 1;
		if (newIndex % this->WIDTH == 0) newIndex -= this->WIDTH;
		break;
	case SNAKE_UP:
		newIndex = index - this->WIDTH;
		if (newIndex < 0) newIndex += this->length;
		break;
	case SNAKE_DOWN:
		newIndex = index + this->WIDTH;
		if (newIndex >= this->length) newIndex -= this->length;
		break;
	case SNAKE_LEFT:
		newIndex = index - 1;
		if (newIndex % this->WIDTH == this->WIDTH-1 || newIndex <0) newIndex += this->WIDTH;
		break;
	default:
		printf_s("ERROR! Illegal direction!  :   %d   \n", direction);
		return 1;
	}
	dirMutex.unlock();
	ListElem<int>* curr = *listElem;
	int oldIndex;

	if (this->field[newIndex] > 0) {
		printf_s("TOTALLY LOST; LMAOOO\n");
		this->printField();

		this->gameState.store(SNAKE_GAMESTATE_LOST);
	}
	else {

		//Frucht
		if (this->field[newIndex] == -1) {
			printf_s("FRUCHT!\n");
			for (int i = 0; i < this->body->getSize(); i++) {
				this->field[*(curr->element)] += SNAKE_GROWTH_PER_FRUIT;
				curr = curr->next;
			}

			controller->refreshIndex(this->generateNewFood());
		}
		this->illegalDirection.store( (this->direction + 2) % 4);

		oldIndex = this->head;
		this->head = newIndex;

		this->field[newIndex] = this->field[this->body->getLast()] + 1;

		this->body->addBack(newIndex);


		if (this->gameState.load()) {
		this->controller->view->refreshIndex(oldIndex);

		this->controller->view->refreshIndex(newIndex);
		}
	

	}



	return 0;
}

//TODO remove this function: debug
void Snakemodel::printField() {

	std::string ret = "";
	for (int i = 0; i < this->HEIGHT; i++) {
		ret += "[";
		for (int j = 0; j < this->WIDTH; j++) {
			ret += "\t" + std::to_string(this->field[i*WIDTH + j]);
		}
		ret += "]\n";
	}
	printf_s(ret.c_str());
}

//TODO remove this function, debug
void printValues(SingleLinkedList<int>* l) {
	std::string str = "VALUES: [";

	ListElem<int>** sP = l->getElemP();
	ListElem<int>* curr = *sP;

	for (int i = 0; i < l->getSize(); i++) {


		str += std::to_string(*curr->element);
		str += "-";
		curr = curr->next;
	}

	str += "]\n\n\n";
	printf_s(str.c_str());
}