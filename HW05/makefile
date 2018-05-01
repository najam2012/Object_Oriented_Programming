all: cf

cf: main.o cell.o connectfourabstract.o connectfourdiag.o connectfourplus.o connectfourplusundo.o
	g++ main.o cell.o connectfourabstract.o connectfourdiag.o connectfourplus.o connectfourplusundo.o -o exe

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

cell.o: cell.cpp
	g++ -std=c++11 -c cell.cpp

connectfourabstract.o: connectfourabstract.cpp
	g++ -std=c++11 -c connectfourabstract.cpp

connectfourdiag.o: connectfourdiag.cpp
	g++ -std=c++11 -c connectfourdiag.cpp

connectfourplus.o: connectfourplus.cpp
	g++ -std=c++11 -c connectfourplus.cpp

connectfourplusundo.o: connectfourplusundo.cpp
	g++ -std=c++11 -c connectfourplusundo.cpp

clean:
	rm *.o exe