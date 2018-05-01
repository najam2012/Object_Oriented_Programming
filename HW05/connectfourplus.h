// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourplus.h.
//This is the interface for the class ConnectFourPlus.
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "connectfourabstract.h"

namespace SelcukConnectFour
{
	class ConnectFourPlus : public ConnectFourAbstract {
	public:
		ConnectFourPlus();
		ConnectFourPlus(int heightValue, int widthValue);
	protected:
		virtual int checkWinner(char symbol);
	};
}//SelcukConnectFour

#endif//CONNECTFOURPLUS_H
