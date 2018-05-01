// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourdiag.h.
//This is the interface for the class ConnectFourDiag.

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H
#include "connectfourabstract.h"

namespace SelcukConnectFour
{
	class ConnectFourDiag : public ConnectFourAbstract
	{
	public:
		ConnectFourDiag();
		ConnectFourDiag(int heightValue, int widthValue);
	private:
		virtual int checkWinner(char symbol);
	};
}//SelcukConnectFour


#endif//CONNECTFOURDIAG_H
