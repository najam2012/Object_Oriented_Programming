// Author: Islam Goktan Selcuk
// Number: 141044071
// file: GTUSetInt.java

interface GTUSetInt<T> {
	int size();
	boolean empty();
	void insert(final T element) throws GTUSetException;
	int max_size();
	void clear();
	GTUSet<T>.GTUIterator<T> begin();
	GTUSet<T>.GTUIterator<T> end();
	void erase(final T element) throws GTUSetException;
	GTUSet<T>.GTUIterator<T> find(final T element)  throws GTUSetException;
	int count(final T element);
	GTUSet<T> intersection(final GTUSet<T> set2) throws GTUSetException;
}
