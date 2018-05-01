import java.lang.reflect.Array;

class GTUSet<T> implements GTUSetInt<T> {
	// bir birimlik bir array olusturulur ve kapasitesi 1 e esitlenir.
	public GTUSet() {
		counter = 0;
		capacity = 1;
		arr = (T[])new Object[1];
	}

	public GTUSet(Class<T[]> cls) {
		counter = 0;
		capacity = 1;
		arr = cls.cast(Array.newInstance(cls.getComponentType(), 1));
	}
	
        // Eger array'de yeterli yer yoksa array iki katina cikarilir
	private void resizeCapacity(int theCapacity) {
		if(theCapacity != capacity) {
			T[] temp = 
				(T[]) Array.newInstance(arr.getClass().getComponentType(), theCapacity);
			System.arraycopy(arr, 0, temp, 0, size());
			capacity = theCapacity;
			arr = temp;
		}
	}

	public int size() {return counter;}
	
	public boolean empty() { return counter == 0;}
	
	public void insert(final T element) throws GTUSetException
	{
            // eger set zaten gonderilen elemana sahipse exception firlatilir.
		for(int i = 0; i < size(); i++)
			if(arr[i] == element)
				throw new GTUSetException("Set already has this element");
		if(counter >= capacity)
			resizeCapacity(capacity * 2);
		
		arr[counter++] = element;
	}
	
	public int max_size() { return capacity; }
	
        // array temizlenir ve kapasitesi 1 e dusurulur
	public void clear() {
		counter = 0;
		capacity = 1;
		arr = (T[]) Array.newInstance(arr.getClass().getComponentType(), 1);;
	}
	
	final public GTUIterator<T> begin() {
		return new GTUIterator(0); 
	}
	
	final public GTUIterator<T> end() {
		return new GTUIterator(size());
	}
	
	public void erase(T element) throws GTUSetException{
		int found = 0;
		int i;
		// gecerli eleman arrayde bulunur ve silinir.
                for(i = 0; i < size() && found == 0; i++)
			if(arr[i] == element)
				found = 1;
                // array bir birim kaydirilir.
		if(found == 1) {
			for(i = i - 1; i+1 < size(); i++)
				arr[i] = arr[i+1];
			counter--;
		}
	}
	
	public GTUIterator<T> find(T element) throws GTUSetException {
		T temp;
		int indexOfElement = 0;
		int found = 0;
                // Bulunan elemanin indexi kaydedilir.
		for(int i = 0; i < size() && found == 0; i++)
			if(arr[i] == element) {
				found = 1;
				indexOfElement = i;
			}
		// eger eleman bulunamazsa end() dondurulur.
		if(found == 0)
			return end(); 
		return new GTUIterator(indexOfElement);
	}
	
	final public int count(final T element) {
		int counter = 0;
		for(int i = 0; i < size(); i++)
			if(arr[i] == element)
				counter++;
		return counter;
	}
	
	public GTUSet<T> intersection(final GTUSet<T> set2) throws GTUSetException {
		GTUSet<T> set3 = new GTUSet();
                // tum elemanlar karsılastirilip 3. kesisimlerinden ucuncu 
                // bir set olusturulur.
		for(int i = 0; i < size(); i++)
			for(int j = 0; j < set2.size(); j++) {
				if(arr[i] == set2.arr[j])
					set3.insert(arr[i]);
			}
		return set3;
	}
	
	private GTUIterator iter; // class icindeki iterator islemleri icin
	protected int counter; // eleman sayısını bulmak ve eleman eklemek icin kullanilir
	protected int capacity; // array'in kapasitesi
	protected T[] arr; // set elemanlarini tutar.

	public class GTUIterator<T>  {
		private int index;
		private boolean hasNext;
		private boolean hasPrevious;
		
		final protected int getIndex() { return index; }
		
		public GTUIterator() { 
			index = 0; 
			hasNext = false;
			hasPrevious = false;
		}
		
		public GTUIterator(int index) { 
			this.index = index;
			hasPrevious = false;
			hasNext = false;
			if(index > 0)
				hasPrevious = true;
			if(index < size())
				hasNext = true;
		}
		
		public boolean hasNext() { 
			if(index < size())
				hasNext = true;
			else 
				hasNext = false;
			
			return hasNext;		
		}
	
		public boolean hasPrevious() {
			if(index > 0)
				hasPrevious = true;
			else 
				hasPrevious = false;
			
			return hasPrevious; 
		}
		
		public T next() throws GTUSetException {
			if(!hasNext())
				throw new GTUSetException("There are no more element.");
			index++;
			return (T) arr[index-1];
		}
		
		public T previous() throws GTUSetException {
			if(!hasPrevious())
				throw new GTUSetException("There is no element previous of the index.");
			index--;
			return (T) arr[index+1];
		}
		
		public boolean equals(GTUIterator object2) {
			return index == object2.index;
		}

	}

}
