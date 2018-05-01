import java.lang.reflect.Array;
import javafx.util.Pair;


public class DriverClass {
	
	public static void test() throws GTUSetException {

		try {
			GTUSet<Integer> mySet = new GTUSet<Integer>(Integer[].class);
			GTUSet<Integer> mySet2 = new GTUSet<Integer>(Integer[].class);
			GTUSet<Integer> mySet3 = new GTUSet<Integer>(Integer[].class);
			GTUSet<Integer>.GTUIterator<Integer> setIter = 
					mySet.new GTUIterator<Integer>();
			
			mySet.insert(12);
			mySet.insert(-55);
			mySet.insert(23);
			mySet.insert(8);
			mySet.insert(-1);
			//mySet.insert(23); //for exception 
			System.out.println(">>>>>>> SET OPERATIONS <<<<<<<\n");
			System.out.println(">> Using hasNext() function for loop condition.");
			for(setIter = mySet.begin(); setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.println("\n");
			
			System.out.println(">> Using end() function for loop condition.");
			for(setIter = mySet.begin(); !setIter.equals(mySet.end()); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.println("\n");
			
			System.out.println(">> Erasing element (23).");
			mySet.erase(23);
			for(setIter = mySet.begin(); setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.println("\n");
			
			System.out.println(">> Finding element (-55) with iterator.");
			setIter = mySet.find(-55);
			for( ; setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.println("\n");
			
			// Intersection of two set
			mySet2.insert(-55);
			mySet2.insert(23);
			mySet2.insert(34);
			mySet2.insert(44);
			mySet2.insert(8);
			
			System.out.println(">> Intersection of two set:");
			mySet3 = mySet.intersection(mySet2);
			
			System.out.print("Set1 =  ");
			for(setIter = mySet.begin(); setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.print("\nSet2 =  ");
			for(setIter = mySet2.begin(); setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
			System.out.print("\nIntersection =  ");
			for(setIter = mySet3.begin(); setIter.hasNext(); ) {
				Integer temp = setIter.next();
				System.out.print(temp + " ");
			}
		
			
			System.out.println("\n\n>>>>>>> MAP OPERATIONS <<<<<<<\n");
			
			GTUMap<Integer, Character> myMap = new GTUMap<Integer, Character>();
			GTUMap<Integer, Character> myMap2 = new GTUMap<Integer, Character>();
			GTUMap<Integer, Character> myMap3 = new GTUMap<Integer, Character>();
			
			GTUMap<Integer, Character>.GTUIterator<Integer, Character> mapIterator = 
					myMap.new GTUIterator<Integer, Character>();
			
			Pair<Integer, Character> p1 = new Pair<Integer, Character>(8, 'a');
			myMap.insert(p1);
			p1 = new Pair<Integer, Character>(3, 'c');
			myMap.insert(p1);
			p1 = new Pair<Integer, Character>(34, 'x');
			myMap.insert(p1);
			p1 = new Pair<Integer, Character>(90, 'k');
			myMap.insert(p1);
			
			p1 = new Pair<Integer, Character>(90, 'l');
			myMap2.insert(p1);
			p1 = new Pair<Integer, Character>(3, 'c');
			myMap2.insert(p1);
			p1 = new Pair<Integer, Character>(8, 'a');
			myMap2.insert(p1);
			
			System.out.println("myMap: ");
			for(mapIterator = myMap.begin(0); mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			
			System.out.println("\n>> Map at() function.");
			System.out.println("myMap.at(8): " + myMap.at(8));
			System.out.println("myMap.at(3): " + myMap.at(3));
			System.out.println("myMap.at(34): " + myMap.at(34));
			System.out.println("myMap.at(90): " + myMap.at(90));
			
			
			System.out.println("\n>> Erasing pair (90, k).");
			p1 = new Pair<Integer, Character>(90, 'k');
			myMap.erase(p1);
			System.out.println("myMap: ");
			for(mapIterator = myMap.begin(0); mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			System.out.println("\n");
			
			System.out.println(">> Finding pair (34, x) with iterator.");
			mapIterator = myMap.find(34, 'x');
			for( ; mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			System.out.println("\n");
			
			System.out.println("Map1: ");
			for(mapIterator = myMap.begin(0); mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			
			System.out.println("\nMap2: ");
			for(mapIterator = myMap2.begin(0); mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			
			myMap3 = myMap.intersection(myMap2); 
			
			System.out.println("\n>> Intersection of Map1 and Map2: ");
			for(mapIterator = myMap3.begin(0); mapIterator.hasNext(); ) {
				p1 = mapIterator.next();
				System.out.println("(" + p1.getKey() + ", " + p1.getValue() + ")");
			}
			
			
			
		}
		catch(GTUSetException e) {
			System.out.println("There is an error: " + e);
		}
		
		
	}
}
