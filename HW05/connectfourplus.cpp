// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourplus.cpp.
//This is the implementation for the class ConnectFourPlus.

#include "connectfourplus.h"

namespace SelcukConnectFour {
	ConnectFourPlus::ConnectFourPlus() :ConnectFourAbstract() {}

	ConnectFourPlus::ConnectFourPlus(int heightValue, int widthValue) 
		: ConnectFourAbstract(heightValue, widthValue) {}

	int ConnectFourPlus::checkWinner(char symbol) {
		int result = 0;
		int i, j;
		char lowerCase = symbol + ('a' - 'A'); // converts letter to lowercase

											   // It controls every cell in the board for finding four same symbols
		for (i = 0; i < height && result == 0; i++)
			for (j = 0; j < width && result == 0; j++) {
				// controls from bottom to up
				if (i >= 3 &&
					gameCells[i][j].getCellValue() == symbol &&
					gameCells[i - 1][j].getCellValue() == symbol &&
					gameCells[i - 2][j].getCellValue() == symbol &&
					gameCells[i - 3][j].getCellValue() == symbol) {
					for (int a = 0; a < 4; a++) // converts letters to lowercase
						gameCells[i - a][j].setCell(lowerCase);

					result = 1;
				}
				// controls from left to right
				else if (j <= width - 4 &&
					gameCells[i][j].getCellValue() == symbol &&
					gameCells[i][j + 1].getCellValue() == symbol &&
					gameCells[i][j + 2].getCellValue() == symbol &&
					gameCells[i][j + 3].getCellValue() == symbol) {
					for (int a = 0; a < 4; a++)
						gameCells[i][j + a].setCell(lowerCase);
					result = 1;
				}
			}

		// for symbol 'O' it returns 2 and for symbol 'X' it returns 1
		// because the winner is determined by this data
		if (result == 1 && symbol == 'O')
			//it indicates for pvp user2 is winner, for pve winner is computer
			return 2;

		return result;
	}
}//SelcukConnectFour
