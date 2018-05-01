// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtuset.cpp.
//This is the implemantation for the class GTUSet.

#include "gtuset.h"
#include <iostream>

template<class T>
void GTUSet<T>::setMaxSize(int size) {
	GTUIterator<T> temp(size);
	temp.setCounter(mySet.getCounter());
	temp.setAddress(mySet.getAddress());
	for (int i = 0; i < mySet.getCounter(); i++)
		temp.iterator.get()[i] = mySet.iterator.get()[i];

	this->mySet = temp;
}

template<class T>
int GTUSet<T>::size() const { return mySet.getCounter(); }

template<class T>
void GTUSet<T>::insert(T element)
{
	try {
		GTUIterator<T> temp;
		temp = find(element);
		if(*temp == element)
			throw element;

		if (mySet.getCounter() < mySet.getMaxSize()) {
			mySet.iterator.get()[mySet.getCounter()] = element;
			mySet.setCounter(mySet.getCounter() + 1);
		}
		else {
			mySet.setMaxSize(mySet.getMaxSize() * 2);
			if (mySet.getMaxSize() == 0)
				mySet.setMaxSize(1);

			setMaxSize(mySet.getMaxSize());
			mySet.iterator.get()[mySet.getCounter()] = element;
			mySet.setCounter(mySet.getCounter() + 1);		
		}
	}
	catch(T e) {
		cerr << "You cannot add same element in set or map! " << endl;
	}
}

template<class T>
bool GTUSet<T>::empty() const { return (mySet.getCounter() == 0); };

template<class T>
void GTUSet<T>::clear() {
	GTUIterator<T> temp(0);
	this->mySet = temp;
}

template<class T>
int GTUSet<T>::count(T target) const{
	GTUIterator<T> p;
	for (p = begin(); p != end(); p++)
		if (*p == target)
			return 1;
	return 0;
}

template<class T>
void GTUSet<T>::erase(T element) {
	int found = 0;
	for (int i = 0; i < mySet.getCounter() && !found; i++)
		if (mySet[i] == element)
			found = i;

	for (; found + 1 < mySet.getCounter(); found++)
		mySet.iterator.get()[found] = mySet.iterator.get()[found + 1];

	mySet.setCounter(mySet.getCounter() + 1);
}

template<class T>
GTUIterator<T> GTUSet<T>::begin() const { return GTUIterator<T>(mySet, 0); }

template<class T>
GTUIterator<T> GTUSet<T>::end() const { return GTUIterator<T>(mySet, mySet.getCounter()); }

template<class T>
GTUIterator<T> GTUSet<T>::find(T element) const {
	GTUIterator<T> temp;
	int i = 0;
	for (temp = begin(); temp != end(); temp++, i++)
		if (*temp == element)
			return GTUIterator<T>(mySet, i);

	return end();
}

template<class T>
int GTUSet<T>::max_size() const { return mySet.getMaxSize(); }

template<class T>
int GTUSet<T>::getCounter() const { return mySet.getCounter(); }

template<class T>
int GTUSet<T>::getAddress() const { return mySet.getAddress(); }
