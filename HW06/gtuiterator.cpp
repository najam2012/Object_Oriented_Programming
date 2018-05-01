// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtuiterator.h.
//This is the implemantation for the class GTUIterator.

#include "gtuiterator.h"
#include <iostream>

// Boyutu bir olan bir shared_ptr olusturur.
template<class T>
GTUIterator<T>::GTUIterator() : counter(0), maxSize(1), address(0) {
	std::shared_ptr<T> iterator(new T[maxSize]);
	this->iterator = iterator;
}

template<class T>
GTUIterator<T>::GTUIterator(int ptrSize) 
	: counter(0), maxSize(ptrSize), address(0) {
	try {
		std::shared_ptr<T> iterator(new T[ptrSize]);
		this->iterator = iterator;	
	}
	catch(std::bad_alloc& ba) {
		cerr << "Exception: " << ba.what() << endl;
	}
}

template<class T>
GTUIterator<T>::GTUIterator(const GTUIterator<T>& obj)
	:counter(obj.counter), maxSize(obj.maxSize), address(0)
{
	this->iterator = obj.iterator;
}

template<class T>
GTUIterator<T>::GTUIterator(const GTUIterator<T>& obj, int theAddress)
	:counter(obj.counter), maxSize(obj.maxSize), address(theAddress)
{
	this->iterator = obj.iterator;
}

template<class T>
T GTUIterator<T>::operator*() {
	return iterator.get()[address];
}

template<class T>
T GTUIterator<T>::operator[](int index) {
	return iterator.get()[index];
}

template<class T>
GTUIterator<T> GTUIterator<T>::operator++() {
	++address;
	return GTUIterator<T>(*this, address);
}

template<class T>
GTUIterator<T> GTUIterator<T>::operator++(int ignore) {
	int temp = address;
	++address;
	return GTUIterator<T>(*this, temp);
}

template<class T>
GTUIterator<T> GTUIterator<T>::operator--() {
	--address;
	return GTUIterator<T>(*this, address);
}

template<class T>
GTUIterator<T> GTUIterator<T>::operator--(int ignore) {
	int temp = address;
	--address;
	return GTUIterator(*this, temp);
}

template<class T>
GTUIterator<T>& GTUIterator<T>::operator=(const GTUIterator<T>& rightSide) {
	iterator = rightSide.iterator;
	counter = rightSide.counter;
	address = rightSide.address;
	maxSize = rightSide.maxSize;

	return *this;
}

template<class T>
void GTUIterator<T>::setElement(T element) {
	iterator.get()[counter] = element;
	counter++;
}
