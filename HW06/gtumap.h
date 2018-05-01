// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtumap.h.
//This is the interface for the class GTUMap.


#ifndef GTUMAP_H
#define GTUMAP_H
#include "gtuset.h"
#include <iostream>
#include <memory>
#include <string>
using namespace std;

template<class K, class V>
class GTUMap : public GTUSet< std::pair<K, V> > {
public:
	V & operator[] (const K& k); // k degiskenini key value olarak kullanarak
	// v degiskenini adrese kopyalar

	GTUMap(): signature("map") {}; // map ve set objesini ayırt etmek icin

	class mapIterator {
	public:
		GTUSet<K> first; // map icin key kumesi
		GTUSet<V> second; // map icin value kumesi
	};
	
	string getSignature() const { return signature; }

	mapIterator iter; // key ve value set'lerine ulasmak icin
private:
	string signature;
};

#endif
