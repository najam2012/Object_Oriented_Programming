// Author: Islam Goktan Selcuk
// Number: 141044071
//This is the file connectfourabstract.cpp.
//This is the implementation for the class ConnectFourAbstract.

#include <iostream>
#include "connectfourabstract.h"
#include "cell.h"
#include <fstream>
using namespace std;

namespace SelcukConnectFour
{

	ConnectFourAbstract::ConnectFourAbstract() :width(5), height(5) 
	{
		// 5'e 5'lik bir tahta olusturur
		gameCells = new Cell*[5];

		for (int i = 0; i < 5; i++)
			gameCells[i] = new Cell[5];

		userSequence = "user1";
		gameMode = 'P';
		// tahtadaki tum cell objelerini initialize eder.
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				gameCells[i][j] = Cell('.', i, j, 1);
	}

	ConnectFourAbstract::ConnectFourAbstract(int heightValue, int widthValue)
		: width(widthValue), height(heightValue)
	{
		gameCells = new Cell*[height];

		for (int i = 0; i < height; i++)
			gameCells[i] = new Cell[width];

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				gameCells[i][j] = Cell('.', i, j, 1);
	}

	ConnectFourAbstract::~ConnectFourAbstract() {
		for(int i = 0; i < height; i++)
			delete[] gameCells[i];
		delete[] gameCells;
	}

	void ConnectFourAbstract::resizeTheBoard(int heightValue, int widthValue)
	{

		width = widthValue;
		height = heightValue;

		// parametrelerdeki degerlere gore yeni tahtayı olusturur
		gameCells = new Cell*[height];
		for (int i = 0; i < height; i++)
			gameCells[i] = new Cell[width];
		// tahtadaki Cell objelerini initialize eder
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				gameCells[i][j] = Cell('.', i, j, 1);
	}

	void ConnectFourAbstract::printBoard() const
	{
		char letter = 'a';
		for (int i = 'a'; i < 'a' + width && letter <= 'z'; i++) {
			cout << letter << " ";
			letter++;
		}
		cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				gameCells[i][j].output();
				cout << " ";
			}
			cout << endl;
		}
	}
	
	void ConnectFourAbstract::saveGame(const string& userSequence, const string& fileName)
	{
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

		// writes all board to file
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				outStream << gameCells[i][j].getCellValue();
			outStream << endl;
		}

		outStream.close();
	}

	void ConnectFourAbstract::loadGame(const string& fileName) 
	{
		ifstream inStream;
		char temp;
		int totalCell = 0;
		int heightValue;
		int widthValue;

		inStream.open(fileName.c_str()); // opening file

		// takes data from file
		inStream >> totalCell >> heightValue >> widthValue
			>> userSequence >> gameMode;


		// set living cell number
		ConnectFourAbstract::setLivingCell(totalCell);

		// resize new board
		resizeTheBoard(heightValue, widthValue);

		int i = 0, j = 0;

		// dosya sonuna kadar dosyayi okur
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
	
	int ConnectFourAbstract::play() 
	{
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
			return 1; // It means valid move
		}
	}

	int ConnectFourAbstract::play(int column) {
		int row = height - 1;
		// If desired row is filled by users or computer, row is reduced.
		//>>>>>>Row always initializes to row = size-1 in gameplay function.<<<<<
		while (row >= 0 && (gameCells[row][column].getCellValue() == 'O' ||
			gameCells[row][column].getCellValue() == 'X' ||
			gameCells[row][column].getCellValue() == ' '))
			row--;

		// If there is no row for move return 0
		if (row == -1)
			return 0; // It means invalid move
		else { // // If move is valid, symbol('O' or 'X') is written.
			if (playerTurn % 2 == 0)
				gameCells[row][column] = Cell('X', row, column, 2);
			else if (playerTurn % 2 == 1)
				gameCells[row][column] = Cell('O', row, column, 3);
			return 1; // It means valid move
		}
	}
	
	void ConnectFourAbstract::verticalMoveControl(int result[2], char symbol) {
		int counter = 0; // keeps number of symbols over and over
		int max = 0;     // max number of symbols
		int i, j;
		int lastIndex;

		// bottom to up
		for (j = 0; j < width; j++) {
			for (i = height - 1; i >= 0; i--) {
				// counts number of symbols
				if (gameCells[i][j].getCellValue() == symbol)
					counter++;
				// If there isnt computer symbol, starts counting again
				else if (gameCells[i][j].getCellValue() != symbol) {
					lastIndex = i;
					// If maximum number is found and there is a empty cell,
					// place is assigned to result
					if (counter > max &&
						gameCells[lastIndex][j].getCellValue() == '.') {
						max = counter;
						result[0] = j;
					}
					counter = 0;
				}
			}
		}
		result[1] = max; // maximum number of symbols
	}

	void ConnectFourAbstract::horizontalMoveControl(int result[2], char symbol) {
		int counter = 0;
		int max = 0;
		int y = 0; // place for move
		int i, j, a, k; // counters
		char temp[4] = {}; // It keeps every side by side 4 cells in the board

		result[0] = 0;
		// left to right
		for (k = height - 1; k >= 0; k--) {
			for (i = 0; i <= width - 4; i++) {
				for (j = i, a = 0; a < 4; j++, a++)
					temp[a] = gameCells[k][j].getCellValue();//four cells from board

				counter = 0;
				for (a = 0; a < 4 && counter != -1; a++) {
					if (temp[a] == symbol) // counting symbols
						counter++;
					// If there is a opponent symbol, stops counting
					else if ((symbol == 'X' && temp[a] == 'O') ||
						(symbol == 'O' && temp[a] == 'X'))
						counter = -1;
				}
				if (counter > max) {
					for (int b = 0, y = j - 4; b < 4; b++, y++)
						// If there is a empty cell and down of the cell is filled,
						// assigns place for move
						if (k + 1 == height ||
							gameCells[k + 1][y].getCellValue() != '.')
							if (gameCells[k][y].getCellValue() == '.') {
								result[0] = y;
								max = counter;
							}
				}
			}
		}

		result[1] = max;
	}

	int ConnectFourAbstract::isGameEnd() {
		// eger kazanan birisi varsa veya tahtanin tamami doluysa 1 return et
		if (checkWinner('X') || checkWinner('O') || isBoardFull())
			return 1;
		else
			return 0;
	}

	int ConnectFourAbstract::isBoardFull() const
	{
		int result = 1;
		// It scans every cell in the board
		for (int i = 0; i < height && result == 1; i++)
			for (int j = 0; j < width && result == 1; j++)
				if (gameCells[i][j].getCellValue() == '.')
					result = 0;

		// If there is an empty cell returns 0, otherwise returns 1
		return result;
	}

	int ConnectFourAbstract::checkWinner(char symbol)
	{
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
				// controls left diagonal
				else if (i >= 3 && j >= 3 &&
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

	void ConnectFourAbstract::playGame() {
		int playAgain = 1;

		getSize();
		resizeTheBoard(height, width);
		gameMode = setGameMode();

		while (playAgain == 1) {
			if (gameMode == 'p' || gameMode == 'P') // user1 vs user2
				playAgain = gamePlayForPlayers();
			else if (gameMode == 'c' || gameMode == 'C')
				playAgain = gamePlayForComputer();
		}
	}

	int ConnectFourAbstract::gamePlayForPlayers()
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
						user1 = play(column); // makes move

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
					else if (input == "eof")
						return 0;
					if (user1 == 0 && isFilled == 0 && isSaved == 0)
						cerr << "Invalid move, please try again" << endl;

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
								user2 = play(column);// makes move
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
							else if (input == "eof")
								return 0;
							if (user2 == 0 && isFilled == 0 && isSaved == 0)
								cerr << "Invalid move, please try again" << endl;

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

	int ConnectFourAbstract::gamePlayForComputer() {
		int user1 = 0;
		int computer = 0;
		int isFilled = 0;
		int winner = 0;
		int column;
		string input;
		int isSaved;

		if (userSequence == "user1")
			printBoard();
		// eger oyunu kazanan yoksa yada oyun tahtasında bosluk varsa oyunu surdur
		while (isFilled == 0 && winner == 0) {
			do {
				cout << "Living Cell: " << ConnectFourAbstract::livingCell << endl;
				isSaved = 0;
				cout << "user's move: ";
				input = takeInput(); // getting move from user

				if (input.length() == 1) {
					column = input[0] - 'a';
					user1 = play(column);// makes move
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
				else if (input == "eof")
					return 0;
				if (user1 == 0 && isFilled == 0 && isSaved == 0)
					cerr << "Invalid move, please try again" << endl;

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
			if (winner == 0) {
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

	string const ConnectFourAbstract::takeInput() {
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

			if (input == "SAVE" || input == "save" ||
				input == "LOAD" || input == "load") {
				cin >> txtName; // If save or load is read, takes file name
				len = txtName.length();
				if (len > 4) // checks file name
					if (txtName.substr(len - 4, 4) != ".txt" &&
						txtName.substr(len - 4, 4) != ".TXT") {
						cerr << "Invalid input, please try again: ";
						inputValidity = 0;
					}
					else
						result = input + txtName;
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
				else
					result = letter;

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

		}

		return result;
	}

	void ConnectFourAbstract::getSize() {
		cout << "Enter width:  ";
		int isInt;
		do {
			isInt = 1;
			cin >> width;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				isInt = 0;
			}
			// If the size of the board isnt between 4 and 20, it takes another input
			if (width <= 0 || isInt == 0)
				cerr << "Invalid board size, enter a diffirent value: ";
		} while (width <= 0 || isInt == 0);

		cout << "Enter height: ";
		do {
			isInt = 1;
			cin >> height;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				isInt = 0;
			}
			// If the size of the board isnt between 4 and 20, it takes another input
			if (height <= 0 || isInt == 0)
				cerr << "Invalid board size, enter a diffirent value: ";
		} while (height <= 0 || isInt == 0);
	}

	char ConnectFourAbstract::setGameMode() {
		int len;
		string choice;

		cout << "Choose game mode. (P) or (C): ";

		do {
			cin >> choice;
			len = choice.size();
			// eger inputun uzunlugu 1 den fazlaysa hatali kabul et
			// degilse dogrulugunu kontrol et ve degiskene ata
			if ((choice[0] != 'P' && choice[0] != 'C' &&
				choice[0] != 'p' && choice[0] != 'c') || len != 1)
				cerr << "Invalid choice. Please enter P or C : ";

		} while ((choice[0] != 'P' && choice[0] != 'C' &&
			choice[0] != 'p' && choice[0] != 'c') || len != 1);

		gameMode = choice[0];

		return choice[0];
	}

	char ConnectFourAbstract::choosingClass() {
		int len;
		string choice;

		cout << "Choose Undo(U) or Plus(P) or Diagonal(D). ";

		do {
			cin >> choice;
			len = choice.size();
			if ((choice[0] != 'U' && choice[0] != 'u' &&
				choice[0] != 'P' && choice[0] != 'p' &&
				choice[0] != 'D' && choice[0] != 'd') || len != 1)
				cerr << "Invalid choice. Please enter (U) or (P) or (D): ";

		} while ((choice[0] != 'U' && choice[0] != 'u' &&
			choice[0] != 'P' && choice[0] != 'p' &&
			choice[0] != 'D' && choice[0] != 'd') || len != 1);

		return choice[0];
	}

	int ConnectFourAbstract::livingCell = 0;
	int ConnectFourAbstract::gameOrder = 1; // for multiplayer game
	
}//SelcukConnectFour
