// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourplusundo.h.
//This is the interface for the class ConnectFourPlusUndo.
#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H
#include "connectfourplus.h"
#include <vector>

namespace SelcukConnectFour
{
	class ConnectFourPlusUndo : public ConnectFourPlus {
	public:
		ConnectFourPlusUndo();
		ConnectFourPlusUndo(int heightValue, int widthValue);
		virtual int play();
	private:
		virtual void saveGame(const string& userSequence, const string& fileName);
		virtual void loadGame(const string& fileName);
		void undoMove();
		virtual int gamePlayForPlayers();
		virtual int gamePlayForComputer();
		virtual string const takeInput();
		vector<int> allMoves;
	};
}//SelcukConnectFour

#endif//CONNECTFOURPLUSUNDO_H
