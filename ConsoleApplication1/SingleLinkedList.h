#pragma once
#include <string>
#include <sstream>
#include <iterator>

#define NULL 0
template <typename T>
class ListElem {
public:
	T* element = NULL;
	ListElem* next = NULL;
};

template <typename T>
class SingleLinkedList
{
private:
	ListElem<T>* firstElement;
	ListElem<T>* lastElement;
	unsigned long size;
public:
	SingleLinkedList();
	~SingleLinkedList();

	inline ListElem<T>** getElemP();

	inline int getSize();

	inline int add(const T newElement);

	inline int addBack(const T newElement);

	int push(T * newElement);

	int pushBack(T * newElement);

	std::string to_string();

	T get(unsigned int index);

	T getP(unsigned int index);

	T getLast();
	
	T getLastP();

	int removeElement(unsigned int index);

	int removeAndFreeElem(unsigned int index);

	int forEach(int(*fn)(T ele));

	int forEachInt(int(*fn)(int* ele));

	T begin() { return firstElement->element; }
	T end() { return lastElement->element;  }

	

	SingleLinkedList<T> operator++() {
		this->firstElement = this->firstElement->next;
		return *this;
	}

};


