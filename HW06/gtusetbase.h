// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtusetbase.h.
//This is the interface for the class GTUSetBase.


#ifndef GTUSETBASE_H
#define GTUSETBASE_H
#include <memory>
#include "gtuiterator.h"
#include <string>

template<class T>
class GTUSetBase {
public:
	virtual void insert(T element) = 0;
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual int max_size() const = 0;
	virtual void clear() = 0;
	virtual int count(T target) const = 0;
	virtual void erase(T element) = 0;
	virtual GTUIterator<T> end() const = 0;
	virtual GTUIterator<T> begin() const = 0;
	virtual GTUIterator<T> find(T element) const = 0;
	virtual string getSignature() const = 0;
};


#endif
