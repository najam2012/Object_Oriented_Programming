// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtumap.cpp.
//This is the implemantation for the class GTUMap.

#include <iostream>
#include <memory>
#include "gtumap.h"

template<class K, class V>
V& GTUMap<K, V>::operator[] (const K& k) {
	
	if (iter.second.max_size() == iter.second.getCounter() + 1)
		iter.second.setMaxSize(iter.second.max_size() * 2);

	iter.first.insert(k);

	iter.second.mySet.counter += 1;
	iter.second.setCounter(iter.second.mySet.counter + 1);
	return iter.second.mySet.iterator.get()[iter.second.mySet.counter-1];
}

