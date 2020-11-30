#pragma once
#include <string>
#include <sstream>


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

	inline int getSize();

	inline int add(const T newElement);

	int push(T * newElement);

	int pushBack(T * newElement);

	std::string to_string();

	T get(unsigned int index);

	T getP(unsigned int index);








};


