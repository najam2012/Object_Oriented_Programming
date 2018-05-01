all: hello

hello: main.o
	g++ main.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o exe

