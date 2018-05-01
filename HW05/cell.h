// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file cell.h.
//This is the interface for the class Cell.

#ifndef CELL_H
#define CELL_H
#include <iostream>
using std::cout;

namespace SelcukConnectFour 
{
	class Cell
	{
	public:
		Cell(char ch, int row, int column, int owner);
		Cell();
		// sets cell character
		void setCell(char ch) { cellValue = ch; }
		void output() const { cout << cellValue; }
		// returns character of cell
		char getCellValue() const { return cellValue; };
		// returns column number
		int getCol() const { return position - 'a'; }
	private:
		char position; // indicates column of the board
		int rowNumber;
		char cellValue; // inside of the cell
		int cellOwner; // owner of cell(user1, user2, empty or computer)
	};
}//SelcukConnectFour

#endif //CELL_H
