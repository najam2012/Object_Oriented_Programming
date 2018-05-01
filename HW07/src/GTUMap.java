import java.lang.reflect.Array;
import javafx.util.Pair;

public class GTUMap<K, V> extends  GTUSet< javafx.util.Pair<K,V> > {
	
	public GTUMap() {
		listCapacity = 1; 
		// map'in value degerleri icin bir array olusturulur
		valueList = (V[])new Object[listCapacity]; 
		// key degerleri icin bir set olusturulur.
		keyList = new GTUSet();
	}

	public V at(K k) throws GTUSetException {
		// keyList setindeki eleman bulunarak, elemanın indexi alinir
		// ve array uzerinden eleman dondurulur
		iter = keyList.find(k); 
		return valueList[iter.getIndex()];
	}

	public void insert(final Pair<K, V> p) throws GTUSetException {
		// pair ciftinin key'i keylist set ine insert edilir.
		keyList.insert(p.getKey());
		// find ile elemanın bulunduğu index bulundur
		iter = keyList.find(p.getKey());
		// valueList array ine kaydedilir.
		// eger arrayin boyutu kucukse iki katina cikarilir
		if(listCapacity-1 < iter.getIndex()) {
			V[] temp = 
                            (V[]) Array.newInstance(valueList.getClass().getComponentType(), listCapacity*2);
			System.arraycopy(valueList, 0, temp, 0, listCapacity);
			listCapacity *= 2;
			valueList = temp;
		}
		// indexden faydalanarak eleman array'e kaydedilir.
		valueList[iter.getIndex()] = p.getValue();
	}


	public void erase(final Pair<K, V> p) throws GTUSetException {
		// eleman find fonkuyla keylist'te bulunur ve set classının
		// erase fonksiyonuyla silinir.
		iter = keyList.find(p.getKey());
		// index den faydalanarak valueList ten de silinir.
		int index = iter.getIndex();
		keyList.erase(p.getKey());
		
		// array bir birim geriye kaydirilir.
		for(int i = index; i < size(); i++)
			valueList[i] = valueList[i+1];
		counter--;
	}

	// set class indan yararlanilarak map'in boyutu ve kapasitesi dondurulur.
	public int size() { return keyList.size(); }

	public int max_size() { return listCapacity; }


	public void clear() {
	// once keylist set'i temizlenir
		keyList.clear();
	// valueList array'inin capasitesi 1 e indirilir ve elemanlari temizlenir.
		listCapacity = 1;
		valueList = (V[]) Array.newInstance(valueList.getClass().getComponentType(), 1);
	}

	public boolean empty() { return keyList.empty();}

	public GTUMap<K, V>.GTUIterator<K, V> find(K key, V value) 
                throws GTUSetException{
		// Once keyList set'inin konumu bulunur
                iter = keyList.find(key);
                // iterator yardimiyla value'nun da konumu bulunur
		int valueIndex = iter.getIndex();
		
                // konumlara gore gtumap iterateru olusturulur ve return 
                // edilir.
		GTUMap<K, V>.GTUIterator<K, V> iter2 = 
				new GTUIterator<K, V>(valueIndex, iter);
		
		return iter2;
	}
	
	public GTUMap<K, V>.GTUIterator<K, V> begin(int i) {
		iter = keyList.begin();
                // keyListin baslangic iteratoru ve valueList array'i icin
                // index 0 gonderilir
		GTUMap<K, V>.GTUIterator<K, V> iter2 = 
				new GTUIterator<K, V>(0, iter);
		return iter2;
	}
	
	public GTUMap<K, V>.GTUIterator<K, V> end(int i) {
		iter = keyList.end();
                // son index ve keyList set'inin sonuunu belirten
                // set iteratoru gonderilir.
		GTUMap<K, V>.GTUIterator<K, V> iter2 = 
				new GTUIterator<K, V>(size(), iter);
		return iter2;
	}
	
	public GTUMap<K, V> intersection(final GTUMap<K, V> map2) 
                throws GTUSetException {
		// kesisen elemanlari tutmak icin ucuncu bir map olusturulur
                GTUMap<K, V> map3 = new GTUMap();
                // Set class'indaki intersection fonksiyonu ile ortak key'ler
                // gecici bir sette tutulur.
		GTUSet<K> temp = keyList.intersection(map2.keyList);
		GTUMap<K, V>.GTUIterator<K, V> mapIter;
		Pair<K, V> p;
		
		iter = temp.begin();
		// tum temp setindeki elemanlar map uzerindeki
                // valueList array'inde bulunan value degeri karsilastirilir.
                for(int i = 0; i < temp.size(); i++) {
                    // gecici key elemani karsilastirma icin alinir
			K key = iter.next();
                        // eger key in karsisindaki value da esitse
                        // pair map3 e eklenir.
			if(at(key) == map2.at(key)) {
				mapIter = find(key, null);
				p = mapIter.next();
				map3.insert(p);
			}
		}
		
		return map3;
	}
	
        // map class' ı icerisinde olusturulan set degiskenlerini
        // manipule etmek icin kullanilir.
	protected GTUSet<K>.GTUIterator<K> iter;
        // map icin key degerlerini tutar.
	private GTUSet<K> keyList; 
        // map icin value degerlerini tutar.
	private V[] valueList;
        // valueList'in kapasitesini tutar.
	private int listCapacity;

	public class GTUIterator<K, V>  {
		private int index; // elemanin map icindeki konumu
		private boolean hasNext; // elemanin sonrasinda eleman varligi icin
		// elemanin oncesindeki eleman varligi icin
                private boolean hasPrevious;
		
		private Pair<K, V> p; // key, value ciftini tutar
                // key set'i icin iterator
		private GTUSet<K>.GTUIterator<K> key; 
		
		public Pair<K, V> next() throws GTUSetException {
			//eger bulunulan konumda eleman yoksa exception firlatilir.
                        if(!hasNext())
				throw new GTUSetException("There are no more element.");
			
                        //Once index artirilir, elemanlar uzerinden
                        // pair olsuturulup return edilir.
                        index++;

			K temp = (K)key.next();
			p = new Pair<K, V>(temp, (V) valueList[index-1]);
			return p;
		}
		
		public Pair<K, V> previous() throws GTUSetException {
			if(!hasPrevious())
				throw new GTUSetException("There is no element previous of the index.");
			//Once index azaltilir, elemanlar uzerinden
                        // pair olsuturulup return edilir.
                        index--;
			K temp = (K)key.previous();
			p = new Pair<K, V>(temp, (V) valueList[index+1]);
			return p;
		}
		
                // end() fonksiyonu icin kullanilir.
                // iterator.equals(obj2.end())
		public boolean equals(GTUIterator object2) {
			return index == object2.index;
		}
		
		// iterator'un bulundugu konumu dondurur
		final private int getIndex() { return index; }
		
                
		public GTUIterator() { 
			key = (GTUSet<K>.GTUIterator<K>) keyList.begin();
			index = 0; 
			hasNext = false;
			hasPrevious = false;
		}
		
                // keyList setinin iteratoru ve index degeri alarak
                // iterator olusturulur.
		public GTUIterator(int index, GTUSet<K>.GTUIterator<K> keyIter){ 
			key = keyIter;
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
		
	}
	
}