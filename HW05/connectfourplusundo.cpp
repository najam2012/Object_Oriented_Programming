// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourplusundo.cpp.
//This is the implementation for the class ConnectFourPlusUndo.
#include "connectfourplusundo.h"
#include <fstream>

namespace SelcukConnectFour
{
	ConnectFourPlusUndo::ConnectFourPlusUndo()
		:ConnectFourPlus() {}

	ConnectFourPlusUndo::ConnectFourPlusUndo(int heightValue, int widthValue)
		:ConnectFourPlus(heightValue, widthValue) {}

	string const ConnectFourPlusUndo::takeInput() {
		string input;
		string txtName; // name of txt file
		char letter;	// for move control
		int len;		// length of input
		string result;
		int inputValidity = 0;
		ifstream inputStream;
		ofstream outputStream;

		// If input value isnt valid, takes another input.
		while (inputValidity == 0) {
			cin >> input;
			letter = input[0]; // for users move
			inputValidity = 1; // If there is no error, it breaks loop

			if(input == "undo" || input == "UNDO")
				result = input;
			else if (input == "SAVE" || input == "save" ||
				input == "LOAD" || input == "load") {
				cin >> txtName; // If save or load is read, takes file name
				len = txtName.length();
				if (len > 4) { // checks file name 
					if (txtName.substr(len - 4, 4) != ".txt" &&
						txtName.substr(len - 4, 4) != ".TXT") {
						cerr << "Invalid input, please try again: ";
						inputValidity = 0;
					}
					else
						result = input + txtName;
				}
				else {
					cerr << "Invalid input, please try again: ";
					inputValidity = 0; // If there is an error, loop is continuing
				}
			}
			else if (input.length() == 1) { // checks validity of users move
				if (letter >= 'A' && letter <= 'Z')
					letter += 'a' - 'A';
				if (letter > (width - 1 + 'a') || letter < 'a') {
					cerr << "Invalid input, please try again: ";
					inputValidity = 0;
				}
				else {
					result = letter;
					allMoves.push_back(letter - 'a');
				}
			}
			// dosyadan alinan inputlar icin dosya sonu kontrolu yapar
			else if (cin.eof()) {
				cout << "End of file.\n";
				inputValidity = 1; // donguyu bitirmek icin 1 atanir
				return "eof";
			}
			else {
				cerr << "Invalid input, please try again: ";
				inputValidity = 0;
			}

			// eger load yapilan dosyadan bir sorun varsa baska bir dosya ismi
			// alinir
			if (inputValidity == 1 && (input == "LOAD" || input == "load")) {
				inputStream.open(txtName.c_str());
				if (inputStream.fail()) {
					cerr << "Invalid input, please try again: ";
					inputValidity = 0; //eger dosya acilmiyorsa baska bir dosya alir.
				}
				inputStream.close();
			}
			// eger save yapilan dosyadan bir sorun varsa baska bir dosya ismi
			// alinir
			else if (inputValidity == 1 && (input == "SAVE" || input == "save")) {
				outputStream.open(txtName.c_str());
				if (outputStream.fail()) {
					cerr << "Invalid input, please try again: ";
					inputValidity = 0;
				}
				outputStream.close();
			}
			else if (inputValidity == 1 && (input == "UNDO" || input == "undo")) {
				if (allMoves.size() > 0) {

				}
			}

		}

		return result;
	}

	int ConnectFourPlusUndo::gamePlayForPlayers()
	{
		int user1 = 0; // for controlling move validity
		int user2 = 0;
		int winner = 0; // indicates winner of the game
		int isSaved = 0;
		int isFilled = 0; // all board is filling or not
		int row = height - 1; // coordinate of move
		int column; // coordinate of move
		string input;
		playerTurn = 0;
		int isUndo = 0;

		if (userSequence == "user1")
			printBoard();

		// continues as long as there is no winner or there is an empty cell in
		// the board
		while (isFilled == 0 && winner == 0) {
			isFilled = isBoardFull(); // controls empty cells

			if (isFilled == 0 && userSequence != "user2")
				do {
					cout << "Living Cell: " << ConnectFourAbstract::livingCell << endl;
					isSaved = 0;
					cout << "user1's move: ";
					input = takeInput(); // getting move from user1
					if (input.length() == 1) {
						column = input[0] - 'a';
						user1 = ConnectFourAbstract::play(column); // makes move

					}
					else if (input.substr(0, 4) == "save" ||
						input.substr(0, 4) == "SAVE") {
						saveGame("user1", input.substr(4));
						isSaved = 1;
					}
					else if (input.substr(0, 4) == "load" ||
						input.substr(0, 4) == "LOAD") {
						loadGame(input.substr(4));
						return 1;
					}
					else if (input == "undo" || input == "UNDO") {
						undoMove();
						isUndo = 1;
						ConnectFourAbstract::livingCellReducer();
						if(user1 == 1)
							ConnectFourAbstract::livingCellReducer();
					}
					else if (input == "eof")
						return 0;
					if (user1 == 0 && isFilled == 0 && isSaved == 0 && isUndo == 0)
						cerr << "Invalid move, please try again." << endl;
					else if (isUndo == 1 && user1 == 0 && isFilled == 0 && isSaved == 0) {
						printBoard();
						isUndo = 0;
					}
					isFilled = isBoardFull();
					
				} while ((user1 == 0 && isFilled == 0) || isSaved == 1);
				
				playerTurn++;
				ConnectFourAbstract::livingCellCounter();
				
				winner = checkWinner('X'); // checks winner for user1
				printBoard();
				if (winner == 1)
					cout << "Winner is user1.\n";

				// if user1 is not winner, user2 makes move
				if (winner == 0) {
					if (userSequence == "user2")
						userSequence = "none";
					isFilled = isBoardFull();
					if (isFilled == 0)
						do {
							isSaved = 0;
							cout << "user2's move: ";
							input = takeInput(); // getting move from user1
							if (input.length() == 1) {
								column = input[0] - 'a';
								user2 = ConnectFourAbstract::play(column);// makes move
							}
							else if (input.substr(0, 4) == "save" ||
								input.substr(0, 4) == "SAVE") {

								saveGame("user2", input.substr(4));
								isSaved = 1;
							}
							else if (input.substr(0, 4) == "load" ||
								input.substr(0, 4) == "LOAD") {

								loadGame(input.substr(4));
								return 1;
							}
							else if (input == "undo" || input == "UNDO") {
								undoMove();
								isUndo = 1;
								ConnectFourAbstract::livingCellReducer();
								if (user2 == 1)
									ConnectFourAbstract::livingCellReducer();
							}
							else if (input == "eof")
								return 0;
							if (user2 == 0 && isFilled == 0 && isSaved == 0 && isUndo == 0)
								cerr << "Invalid move, please try again" << endl;
							else if (isUndo == 1 && user2 == 0 && isFilled == 0 && isSaved == 0) {
								printBoard();
								isUndo = 0;
							}
							isFilled = isBoardFull();
							
						} while ((user2 == 0 && isFilled == 0) || isSaved == 1);
						playerTurn++;

						ConnectFourAbstract::livingCellCounter();
						
						winner = checkWinner('O');
						printBoard();

						if (winner == 2)
							cout << "Winner is user2.\n";
				}
		}
		// If there is no winner and board is filled, it is executed
		if (winner == 0 && isFilled == 1)
			cout << "Nobody won the game.\n";
		return 0;
	}

	void ConnectFourPlusUndo::undoMove() {
		int len = allMoves.size();
		int column;
		int flag = 0;

		if (len > 0) {
			column = allMoves[len - 1];
			for (int i = 0; i < height && flag == 0; i++)
				if (gameCells[i][column].getCellValue() != '.') {
					flag = 1;
					gameCells[i][column].setCell('.');
				}
			allMoves.pop_back();
		}
	}

	int ConnectFourPlusUndo::gamePlayForComputer() {
		int user1 = 0;
		int computer = 0;
		int isFilled = 0;
		int winner = 0;
		int column;
		string input;
		int isSaved;
		int isUndo;

		if (userSequence == "user1")
			printBoard();
		// eger oyunu kazanan yoksa yada oyun tahtasında bosluk varsa oyunu surdur
		while (isFilled == 0 && winner == 0) {
			isUndo = 0;
			do {
				cout << "Living Cell: " << ConnectFourAbstract::livingCell << endl;
				isSaved = 0;
				cout << "user's move: ";
				input = takeInput(); // getting move from user

				if (input.length() == 1) {
					column = input[0] - 'a';
					user1 = ConnectFourAbstract::play(column);// makes move
				}
				else if (input.substr(0, 4) == "save" ||
					input.substr(0, 4) == "SAVE") {
					saveGame("user1", input.substr(4));
					isSaved = 1;
				}
				else if (input.substr(0, 4) == "load" ||
					input.substr(0, 4) == "LOAD") {
					loadGame(input.substr(4));
					return 1;

				}
				else if (input == "undo" || input == "UNDO") {
					if (allMoves.size() != 0) {
						ConnectFourAbstract::livingCellReducer();
						ConnectFourAbstract::livingCellReducer();
						if (user1 == 1)
							ConnectFourAbstract::livingCellReducer();
					}

					undoMove();
					undoMove();
					isUndo = 1;
				}
				else if (input == "eof")
					return 0;
				if (user1 == 0 && isFilled == 0 && isSaved == 0 && isUndo == 0)
					cerr << "Invalid move, please try again" << endl;
				else if (user1 == 0 && isFilled == 0 && isSaved == 0 && isUndo == 1) {
					printBoard();
					isUndo = 0;
				}
				isFilled = isBoardFull();
			} while ((user1 == 0 && isFilled == 0) || isSaved == 1);

			ConnectFourAbstract::livingCellCounter();

			//if it is valid, makes move
			isFilled = isBoardFull(); // controls empty cells
			winner = checkWinner('X');
			printBoard();
			if (winner == 1)
				cout << "Winner is user.\n";

			// if user isnt winner, computer makes move
			if (winner == 0 && isUndo == 0) {
				cout << "computer's move: ";
				//if it is valid, makes move
				computer = play();
				isFilled = isBoardFull();
				// if move isnt valid, takes another move
				while (computer == 0 && isFilled == 0) {
					computer = play();
					isFilled = isBoardFull();
				}
				ConnectFourAbstract::livingCellCounter();
				winner = checkWinner('O');
				printBoard();
				if (winner == 2)
					cout << "Winner is computer.\n";
			}
		}

		// If there is no winner and board is filled, it is executed
		if (winner == 0 && isFilled == 1)
			cout << "Nobody won the game.\n";

		return 0;
	}

	int ConnectFourPlusUndo::play() {
		// data for winning moves
		int hor[2] = {};        // takes result from functions
		int ver[2] = {};
		// data for prevention moves
		int preventHor[2] = {};
		int preventVer[2] = {};

		int row;
		int column;
		int result = 0; // target place for move
		int found = 0;
		char letter;


		// prevention moves for user
		verticalMoveControl(preventVer, 'X');
		horizontalMoveControl(preventHor, 'X');

		// winning moves
		verticalMoveControl(ver, 'O');
		horizontalMoveControl(hor, 'O');

		// makes the most logical move
		// checks number of symbols side by side or over and over
		if (ver[1] > hor[1])
			result = ver[0];
		else
			result = hor[0];

		// If winning or losing is close, makes that moves
		if (ver[1] == 3)
			result = ver[0];
		else if (hor[1] == 3)
			result = hor[0];
		else if (preventHor[1] == 3)
			result = preventHor[0];
		else if (preventVer[1] == 3)
			result = preventVer[0];

		// there is no logical move then it finds first empty cell
		if (result == 0)
			for (int i = 0; i < height && found == 0; i++)
				for (int j = 0; j < width && found == 0; j++)
					if (gameCells[i][j].getCellValue() == '.') {
						result = j;
						found = 1;
					}

		column = result; // target place
		row = height - 1;

		// for seeing computer move
		letter = static_cast<char>('a' + column);
		cout << letter << endl;

		// If desired row is filled by users or computer, row is reduced.
		//>>>>>>Row always initializes to row = size-1 in gameplay function.<<<<<
		while (row >= 0 && (gameCells[row][column].getCellValue() == 'O' ||
			gameCells[row][column].getCellValue() == 'X'))
			row--;

		// If there is no row for move return 0
		if (row == -1)
			return 0; // It means invalid move
		else { // // If move is valid, symbol('O' or 'X') is written.
			gameCells[row][column] = Cell('O', row, column, 4);
			allMoves.push_back(column);
			return 1; // It means valid move
		}
	}

	void ConnectFourPlusUndo::saveGame(const string& userSequence, const string& fileName) {
		ofstream outStream;
		int currentCell = 0;

		outStream.open(fileName.c_str()); // opening or creating file

										  // count livingCell
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++) {
				if (gameCells[j][i].getCellValue() == 'O' ||
					gameCells[j][i].getCellValue() == 'X')
					currentCell++;
			}

		// writes data to file
		outStream << currentCell << endl
			<< height << " " << width << endl
			<< userSequence << endl
			<< gameMode << endl;

		// Tum yapilan oyun hamlelerini kaydeder. Sonradan hamlelerin
		// geri alinabilmesi icin
		outStream << allMoves.size() << endl;
		for (int i = 0; i < allMoves.size(); i++)
			outStream << allMoves[i] << " ";
		outStream << endl;

		// writes all board to file
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				outStream << gameCells[i][j].getCellValue();
			outStream << endl;
		}	

		outStream.close();
	}
	
	void ConnectFourPlusUndo::loadGame(const string& fileName) {
		ifstream inStream;
		char temp;
		int cellNumber;
		int totalCell = 0;
		int heightValue;
		int widthValue;

		inStream.open(fileName.c_str()); // opening file

		// takes data from file
		inStream >> cellNumber >> heightValue >> widthValue
			>> userSequence >> gameMode;


		// set living cell number
		totalCell = cellNumber;
		ConnectFourAbstract::setLivingCell(totalCell);

		// resize new board
		resizeTheBoard(heightValue, widthValue);

		int totalMove = 0;
		inStream >> totalMove;

		allMoves.clear();
		for (int i = 0; i < totalMove; i++) {
			int temp;
			inStream >> temp;
			allMoves.push_back(temp);
		}

		int i = 0, j = 0;
		// dosya sonuna kadar dosyayi okur
		inStream.get(temp);
		inStream.get(temp);
		while (!inStream.eof()) {
			inStream.get(temp);
			if (temp == '\n') {
				i++;
				j = 0;
			}
			if (i < height && j < width && temp != '\n') {
				if (temp == '.')
					gameCells[i][j++] = Cell(temp, i, j, 1);
				else if (temp == 'X')
					gameCells[i][j++] = Cell(temp, i, j, 2);
				else if (temp == 'O' && (gameMode == 'p' || gameMode == 'P'))
					gameCells[i][j++] = Cell(temp, i, j, 3);
				else if (temp == 'O' && (gameMode == 'c' || gameMode == 'C'))
					gameCells[i][j++] = Cell(temp, i, j, 4);
				else
					gameCells[i][j++].setCell(temp);
			}
		}


		inStream.close();
	}
}//SelcukConnectFour
