// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file cell.cpp.
//This is the implementation for the class Cell.

#include "cell.h"

namespace SelcukConnectFour {

	Cell::Cell(char ch, int row, int column, int owner)
	{
		cellValue = ch;  // objenin tuttugu karakter
		rowNumber = row + 1; // satir numarasi
		position = 'A' + column; // sutun numarasi
		cellOwner = owner; // cell'in sahipligi (user1, empty, user2, comp)
	}

	Cell::Cell() {
		// intentionally empty
	}
}//SelcukConnectFour
