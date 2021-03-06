#pragma once
#include "SingleLinkedList.h"



//TODO: ADD a simpleList with basic implementation, so SingleLinkedList can accept values instead of references and allocate memory to store these and later 
//smartly delete them
class simpleList {

	class simpleElem {
		void* e;
		simpleElem* next;
	};

	simpleElem* start = NULL;

	void push(void* newElem) {

	}

};

template <typename T>
SingleLinkedList<T>::SingleLinkedList() {
	size = 0;
	firstElement = NULL;
	lastElement = NULL;
}


template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {

}

template<typename T>
inline ListElem<T>** SingleLinkedList<T>::getElemP()
{
	return &firstElement;
}

template<typename T>
inline int SingleLinkedList<T>::getSize()
{
	return size;
}


//TODO: see above, allocate memory for newElement
template <typename T>
inline int SingleLinkedList<T>::add(T newElement) {
	int* newP = (int*)malloc(sizeof(T));
	*newP = newElement;
	this->push(newP);
	return newElement;
}

template <typename T>
inline int SingleLinkedList<T>::addBack(T newElement) {
	int* newP = (int*)malloc(sizeof(T));
	*newP = newElement;
	this->pushBack(newP);
	return newElement;
}

template <typename T>
inline int SingleLinkedList<T>::push(T* newElement) {
	ListElem<T>* newLink = new ListElem<T>();
	newLink->element = newElement;
	newLink->next = firstElement;
	firstElement = newLink;
	if (size == 0) {
		lastElement = firstElement;
	}
	size++;

	return 0;
}

template <typename T>
inline int SingleLinkedList<T>::pushBack(T* newElement) {

	ListElem<T>* newLink = new ListElem<T>();
	newLink->element = newElement;
	if (lastElement != NULL) lastElement->next = newLink;
	lastElement = newLink;

	if (size == 0) {
		firstElement = lastElement;
	}
	size++;

	return 0;
}

template <typename T>
std::string SingleLinkedList<T>::to_string() {
	if (this->size == 0) return "[ ]";
	std::string ret = "";
	std::stringstream sstream;

	sstream << "[ ";
	ListElem<T>* currentElem = firstElement;
	for (unsigned int i = 0; i < size; i++) {
		T actual = *(currentElem->element);
		currentElem = currentElem->next;
		if (i != 0) {
			sstream << " , ";
		}
		sstream << actual;
	}
	sstream << " ]";
	ret = sstream.str();
	return ret;
}


template <typename T>
T SingleLinkedList<T>::get(unsigned int index) {
	ListElem<T>* cur = firstElement;
	for (unsigned int i = 0; i < index; i++) {
		cur = cur->next;
	}
	return *(cur->element);
}

template <typename T>
T SingleLinkedList<T>::getP(unsigned int index) {
	ListElem<T>* cur = firstElement;
	for (unsigned int i = 0; i < index; i++) {
		cur = cur->next;
	}
	return cur->element;
}

template<typename T>
inline T SingleLinkedList<T>::getLast()
{
	return *lastElement->element;
}

template<typename T>
inline T SingleLinkedList<T>::getLastP()
{
	return lastElement->element;
}

template <typename T>
int SingleLinkedList<T>::removeElement(unsigned int index) {
	ListElem<T>* ptr = firstElement;
	if (index == 0) {
		firstElement = firstElement->next;

	}
	else {
		ListElem<T>* ptr2;
		for (unsigned int i = 0; i < index - 1; i++) {
			ptr = ptr->next;
		}

		ptr2 = ptr;
		ptr = ptr2->next;
		if (index == size - 1) {
			lastElement = ptr2;
		}
		ptr2->next = ptr->next;
	}
	free(ptr);
	size--;
	if (size == 0) {
		firstElement = NULL;
		lastElement = NULL;
	}
	return 0;

}

template <typename T>
int SingleLinkedList<T>::removeAndFreeElem(unsigned int index) {
	ListElem<T>* ptr = firstElement;
	if (index == 0) {
		firstElement = firstElement->next;

	}
	else {
		ListElem<T>* ptr2;
		for (unsigned int i = 0; i < index - 1; i++) {
			ptr = ptr->next;
		}
		ptr2 = ptr;
		ptr = ptr2->next;
		ptr2->next = ptr->next;
	}
	free(ptr->element);
	free(ptr);
	size--;
	if (size == 0) {
		firstElement = NULL;
		lastElement = NULL;
	}
	return 0;

}

template<typename T>
inline int SingleLinkedList<T>::forEach(int(*fn)(T ele))
{

	ListElem<T>* curr = this->firstElement;
	for (int i = 0; i < this->size; i++) {
		if (curr == NULL) {
			printf_s("ERROR DURING LIST->forEach ... element NULL \n");
			return 1;
		}

		fn(curr->element);
		curr = curr->next;
	}

	return 0;
}

template<typename T>
inline int SingleLinkedList<T>::forEachInt(int(*fn)(int* ele))
{

	ListElem<T>* curr = this->firstElement;
	for (unsigned int i = 0; i < this->size; i++) {
		if (curr == NULL) {
			printf_s("ERROR DURING LIST->forEach ... element NULL \n");
			return 1;
		}

		fn(((int*)(curr->element)));
		curr = curr->next;
	}

	return 0;
}