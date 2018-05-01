// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourdiag.cpp.
//This is the implementation for the class ConnectFourDiag.

#include "connectfourdiag.h"

namespace SelcukConnectFour
{
	ConnectFourDiag::ConnectFourDiag()
		:ConnectFourAbstract() {}

	ConnectFourDiag::ConnectFourDiag(int heightValue, int widthValue)
		:ConnectFourAbstract(heightValue, widthValue) {}

	int ConnectFourDiag::checkWinner(char symbol) {
		int result = 0;
		int i, j;
		char lowerCase = symbol + ('a' - 'A'); // converts letter to lowercase

											   // It controls every cell in the board for finding four same symbols
		for (i = 0; i < height && result == 0; i++)
			for (j = 0; j < width && result == 0; j++) {
				// controls left diagonal
				if (i >= 3 && j >= 3 &&
					gameCells[i][j].getCellValue() == symbol &&
					gameCells[i - 1][j - 1].getCellValue() == symbol &&
					gameCells[i - 2][j - 2].getCellValue() == symbol &&
					gameCells[i - 3][j - 3].getCellValue() == symbol) {
					for (int a = 0; a < 4; a++)
						gameCells[i - a][j - a].setCell(lowerCase);

					result = 1;
				}
				// controls right diagonal
				else if (i >= 3 && j <= width - 4 &&
					gameCells[i][j].getCellValue() == symbol &&
					gameCells[i - 1][j + 1].getCellValue() == symbol &&
					gameCells[i - 2][j + 2].getCellValue() == symbol &&
					gameCells[i - 3][j + 3].getCellValue() == symbol) {
					for (int a = 0; a < 4; a++)
						gameCells[i - a][j + a].setCell(lowerCase);

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
