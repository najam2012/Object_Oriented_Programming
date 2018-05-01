// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourabstract.h.
//This is the interface for the class ConnectFourAbstract.

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H
#include "cell.h"
#include <string>
using namespace std;

namespace SelcukConnectFour
{
	class ConnectFourAbstract
	{
	public:
		void test();
		ConnectFourAbstract();
		ConnectFourAbstract(int heightValue, int widthValue);
		virtual ~ConnectFourAbstract();
		static char choosingClass();
		void playGame();
		int play(int column);
		virtual int play();
		int isGameEnd();
		inline int getWidth() const { return width; };
		inline int getHeight() const { return height; };
		void printBoard() const;

		void resizeTheBoard(int heightValue, int widthValue);
		static void setLivingCell(int temp) { livingCell = temp; };
		static const int totalLivingCell() { return livingCell; };
	protected:
		Cell **gameCells;
		int width;
		int height;
		char gameMode;
		string userSequence;
		int playerTurn;
		static int livingCell; // number of living cell
		static int gameOrder; // indicates which object start the game

		virtual string const takeInput();
		inline static int livingCellCounter() { return ++livingCell; };
		inline static int livingCellReducer() { return --livingCell; };
		virtual int gamePlayForPlayers();
		virtual int gamePlayForComputer();
		char setGameMode();
		void getSize();
		virtual int checkWinner(char symbol);
		int isBoardFull() const;
		virtual void saveGame(const string& userSequence, const string& fileName);
		virtual void loadGame(const string& fileName);
		void verticalMoveControl(int result[2], char symbol);
		void horizontalMoveControl(int result[2], char symbol);

	};

}//SelcukConnectFour

#endif // CONNECTFOURABSTRACT_H
