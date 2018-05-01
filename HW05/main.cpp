#include <iostream>
#include "cell.h"
#include "connectfourabstract.h"
#include "connectfourdiag.h"
#include "connectfourplus.h"
#include "connectfourplusundo.h"

using namespace std;
using namespace SelcukConnectFour;

int main() {

	char choice = ConnectFourAbstract::choosingClass();
	
	ConnectFourAbstract *game;

	if (choice == 'U' || choice == 'u')
		game = new ConnectFourPlusUndo();
	else if (choice == 'P' || choice == 'p')
		game = new ConnectFourPlus();
	else
		game = new ConnectFourDiag();
	
	game->playGame();
}
