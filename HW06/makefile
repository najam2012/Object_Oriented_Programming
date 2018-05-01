all: cf

cf: main.o gtuiterator.o gtuset.o gtumap.o 
	g++ main.o gtuiterator.o gtuset.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

gtuiterator.o: gtuiterator.cpp
	g++ -std=c++11 -c gtuiterator.cpp

gtumap.o: gtumap.cpp
	g++ -std=c++11 -c gtumap.cpp

gtuset.o: gtuset.cpp
	g++ -std=c++11 -c gtuset.cpp

clean:
	rm *.o exe
