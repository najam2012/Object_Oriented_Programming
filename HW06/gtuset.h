// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtuset.h.
//This is the interface for the class GTUSet.

#ifndef GTUSET_H
#define GTUSET_H
#include "gtusetbase.h"
#include "gtuiterator.h"
#include "gtuiterator.cpp"
#include <memory>
#include <iostream>
#include <string>



template<class T>
class GTUSet : public GTUSetBase<T> {

public:
	class DivideByZero {};

	GTUSet() : signature("set") {};

	typedef GTUIterator<T> Iterator;

	// sahip oldugu eleman sayisini dondurur
	virtual int size() const;

	// kumeye eleman eklemek icin kullanilir.
	virtual void insert(T element);

	// kumenin bos olup olmadigini kontrol eder.
	virtual bool empty() const;
	
	// set'i bos bir set'e donusturur.
	virtual void clear();

	// target'in set deki sayisini dondurur
	virtual int count(T target) const;
	
	// set'den eleman siler.
	virtual void erase(T element);

	// address degiskeni 0 olan iterator'u dondurur
	virtual GTUIterator<T> begin() const;
	// address 'i iteratorun sonunu belirten bir iterator dondurur.
	virtual GTUIterator<T> end() const;

	// set icerisindeki elemani bulup, konumunun bulundugu iteratoru dondurur.
	virtual GTUIterator<T> find(T element) const;

	virtual int max_size() const;

	// getter'lar ve setter'lar
	int getAddress() const;

	int getCounter() const;

	void setCounter(int theCounter) { mySet.setCounter(getCounter()); }

	void setMaxSize(int size);

	virtual string getSignature() const { return signature; }

	string signature;

	GTUIterator<T> mySet; // iterator kullanilarak shared_ptr islemleri 
	// soyutlanir.
};

#endif
