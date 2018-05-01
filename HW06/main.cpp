// >>>>>>>> HW-6 <<<<<<<<
// Author: Islam Goktan Selcuk
// Number: 141044071

#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <cstring>
#include "gtusetbase.h"
#include "gtuset.h"
#include "gtuset.cpp"
#include "gtumap.h"
#include "gtumap.cpp"
#include "gtuiterator.h"
using namespace std;

template<class T>
shared_ptr<GTUSet<T> > setIntersection(const GTUSetBase<T>& set1, const GTUSetBase<T>& set2) {
	GTUIterator<T> p1;
	GTUIterator<T> p2;


	if(set1.getSignature() == "set" && set2.getSignature() == "set") {
		shared_ptr< GTUSet<T> > intersection(new GTUSet<T>);

		for (p1 = set1.begin(); p1 != set1.end(); p1++)
			for (p2 = set2.begin(); p2 != set2.end(); p2++) {
				if (*p1 == *p2) {
					intersection->insert(*p1);
				}
			}

		return intersection;
	}
}



int main(int, char**) {
	shared_ptr< GTUSetBase<char> > A(new GTUSet<char>);
	shared_ptr< GTUSetBase<char> > B(new GTUSet<char>);
	shared_ptr< GTUSetBase<char> > C(new GTUSet<char>);
	GTUSet<char> D;
	GTUSet<char>::Iterator p;

	GTUMap<char, char> M;
	cout << M.getSignature() << endl; 
	
	A->insert('x');
	//A->insert('x');
	A->insert('y');
	A->insert('z');
	A->insert('&');
	A->insert('a');

	
	B->insert('&');
	B->insert('A');
	B->insert('y');
	B->insert('a');
	B->insert('d');

	C = setIntersection(*A, *B);

	cout << endl << ">>>>Demonstration of Set Class<<<<" << endl;

	cout << ">>Set A: { ";
	for (p = A->begin(); p != A->end(); p++)
		cout << *p << ", ";

	cout << "}" << endl << ">>Set B: { ";
	for (p = B->begin(); p != B->end(); p++)
		cout << *p << ", ";
	
	cout << "}" << endl << ">>>>Intersection of A and B: { ";	
	for (p = C->begin(); p != C->end(); p++)
		cout << *p << ", ";
	cout << "}" << endl;

	

	cout << endl << ">>>> Demonstration of Map Class <<<<" << endl;
	GTUMap<char, int> m;
	GTUIterator<char> i;
	GTUIterator<int> k;

	m['x'] = 3;
	m['y'] = 4;
	m['z'] = 5;
	m['a'] = 6;
	//m['x'] = 3; // It throws exception

	i = m.iter.first.begin();
	k = m.iter.second.begin();
	for( ; i != m.iter.first.end(); i++, k++)
		cout << "m[" << *i << "] = " << *k << endl;


/*	
	m.iter.first.insert(12);
	GTUIterator<int> p;
	p = m.iter.first.begin();
	cout << *p;
	//m[0] = 1;

	cout << *(m.iter.first.mySet)
		<< ",  Counter: " << m.iter.first.getCounter() << endl;
	m['1'] = '3';
	cout << *(++m.iter.first.mySet)
		<< ",  Counter: " << m.iter.first.getCounter() << endl;
	m['2'] = '4';
	//p = m.iter.first.begin();

	shared_ptr< GTUMap<char, char> > a(new GTUMap<char,char>);
	//a = &m;
	/*
	GTUSet<char>::Iterator p;
	GTUSet<char>::Iterator p2;
	

	


	m['1'] = '3';
	m['2'] = '4';
	m['3'] = '5';

	p2 = m.iter.second.begin();
	for(p = m.iter.first.begin(); p != m.iter.first.end(); p++, p2++)
		cout << *p << " " << *p2 << endl;
	*/


	cout << endl << "End of program!" << endl;
	return 0;
}
