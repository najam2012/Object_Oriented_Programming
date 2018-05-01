// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file gtuiterator.h.
//This is the interface for the class GTUIterator.

#ifndef GTUITERATOR_H
#define GTUITERATOR_H
#include <memory>
#include <iostream>

using namespace std;

template<class T>
class GTUIterator {
public:
	GTUIterator(); // maxSize in bir oldugu bir obje olusturur

	GTUIterator(int ptrSize); // ptrSize boyutunda bir shared_ptr arrayi olusturur.

	GTUIterator(const GTUIterator<T>& obj); // copy constructor

	// address degiskenini atandigi ve obj'nin atandigi constructor
	GTUIterator(const GTUIterator<T>& obj, int theAddress);

	/* Share_ptr arrayinde address degiskeni index olarak kullanilir ve 
		arraydeki deger dondurulur. */		
	T operator*(); 

	/* iterator arrayinden index'i kullanarak deger döndürür. */
	T operator[](int index);

	// address degerini artırarak iterator dondurur. 
	GTUIterator<T> operator++();

	// asil iteratorun adresi artirilirken, adresi artirilmayan gecici bir 
	// iterator dondurur	
	GTUIterator<T> operator++(int ignore);

	GTUIterator<T> operator--();

	GTUIterator<T> operator--(int ignore);

	GTUIterator<T>& operator=(const GTUIterator<T>& rightSide);

	// verilen element iterator arrayine eklenir ve counter degiskeni bir
	// artirilir.
	virtual void setElement(T element);

	// iki iterator karsilastirilir
	friend bool operator !=(const GTUIterator<T>& it1, const GTUIterator<T>& it2) {
		return (&it1.iterator.get()[it1.address] != &it2.iterator.get()[it2.address]);
	}

	friend bool operator ==(const GTUIterator<T>& it1, const GTUIterator<T>& it2) {
		return !(it1 != it2);
	}
	
	// getter'lar ve setter'lar
	int getCounter() const { return counter; }

	void setCounter(int theCounter) { counter = theCounter; }

	void setMaxSize(int theSize) { maxSize = theSize; }

	void setAddress(int theAdress) {address = theAdress; }

	int getMaxSize() const { return maxSize; }

	int getAddress() const { return address; }

	std::shared_ptr<T> iterator; // setteki degerleri tutar.
	int counter; //>> eleman eklerken arrayin indexini tutar.
private:
	int address; //>> iterator icin kullanılır. Dongulerde ilerlerken
	int maxSize; //>> memory'de shared ptr icin ayirilan yer
};

#endif
