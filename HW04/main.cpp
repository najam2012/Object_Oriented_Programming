
/*>>>>>>>>>>>>>>>>>>>> HW-4 Connect Four <<<<<<<<<<<<<<<<<<<<<\\
* Homework-4
*
* Author: Islam Goktan SELCUK
* No: 141044071
*
*   Program is the game of Connect Four. Game has two gameplay mode.
*     They are user versus user and computer versus user.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class ConnectFour {
public:

	ConnectFour();
	// initializes height and width of board according to the parameters
	ConnectFour(int heightValue, int widthValue);
	// initializes board according to the file
	ConnectFour(const string& fileName);
	~ConnectFour();
	// compares two objects(game)
	bool operator ==(const ConnectFour& other);
	bool operator !=(const ConnectFour& other);
	// checks validity of file name
	static string const takeFileName();
	// reads file and builds the board and fills the board
	void fileReader(string fileName);

	inline int getWidth() const { return width; };
	inline const int getHeight() const { return height; };

	inline string getUserSequence() const { return userSequence; };
	inline char  getGameMode() const { return gameMode; }; // pvp or pve
	char setGameMode(); // sets pvp or pve game
	void printBoard() const;

	// helps for player turn
	int getPlayerTurn() const { return playerTurn; };
	// indicates game is ended or not
	int isGameEnd();
	static const int totalLivingCell() { return livingCell; };	
	static void setLivingCell(int temp) { livingCell = temp; };
	// returns turn of game objects
	static int getGameOrder() { return gameOrder; };
	// sets turn of game objects
	static void setGameOrder(int temp) { gameOrder = temp; };
	// for user interface, indicates which game is start
	static char singlePlayerOrMultiPlayer();
// takes file name to user and it plays game until the end for singleplayer mode 
	void playGame(); 
	// it plays game until the end for multiplayer mode
	int playGameForMulti(string objectName);
	// set game ending status
	inline void setGameStatus(int temp) { gameStatus = temp; };
	inline int getGameStatus() { return gameStatus; };


private:
	class Cell {
	public:
		Cell operator++(); // cell objesinin sahipligini degistirir. 
		Cell operator++(int);
		bool operator==(const Cell& other) const; // compares two cell objects
		// prints all cell object information
		friend ostream& operator <<(ostream& output, Cell const& obj)  {
			output << "Cell Info: " << endl
			<< "Position: " << obj.position << endl
			<< "Row Number: " << obj.rowNumber << endl
			<< "Cell Value: " << obj.cellValue << endl;

			// if cellOWner equals to one, then cell is empty
			if(obj.cellOwner == 1)
				output << "Cell Owner: " << "empty" << endl;
			// if it equals to 2, owner of cell is user1
			else if(obj.cellOwner == 2)
				output << "Cell Owner: " << "user1" << endl;
			else if(obj.cellOwner == 3)
				output << "Cell Owner: " << "user2" << endl;
			else if(obj.cellOwner == 4)
				output << "Cell Owner: " << "computer" << endl;

			return output;
		};

		// takes cell information to user
		friend istream& operator >>(istream& input, Cell& obj) {
			// temporary variables
			char pos;
			int row;
			char cellVal;
			cout << "Enter information of the cell:\n"
				 << "Position (A, B, C...): ";
			input >> pos;

			cout << "Row number (1, 2, 3...): ";
			input >> row;
			// controls end of file
			while(input.fail()) {
				input.clear();
				input.ignore();
				cout << "Row number (1, 2, 3...): ";
				input >> row;
			}

			cout << "Value of Cell (.), (X), (O): ";
			input >> cellVal;

			cout << "Enter owner of Cell (1 for (empty), "
				 << "2(user1), 3(user2), 4(comp)): ";
			input >> obj.cellOwner;

			// assining member variables
			obj.position = pos;
			obj.rowNumber = row;
			obj.cellValue = cellVal;
			return input;
		};
		// initializes cell object according to parameters
		// ch: character for board cell
		// row: row number, column: alphabetical location
		// owner: owner of cell(user1, user2, empty or computer)
		Cell(char ch, int row, int column, int owner);
		Cell();

		// returns character of cell
		char getCellValue() const { return cellValue; };
		// returns column number
		int getCol() const { return position - 'a'; }
		// sets cell character
		void setCell(char ch) { cellValue = ch; }
		void output() const { cout << cellValue; }
	private:
		char position; // indicates column of board
		int rowNumber; 
		char cellValue; // inside of cell
		int cellOwner; // owner of cell(user1, user2, empty or computer) 
	};

	inline static int livingCellCounter() { return ++livingCell; };
	void getSize(); // size of board, width and height
	void resizeTheBoard(int heightValue, int widthValue);
	// for intelligent move and game compare
	void horizontalMoveControl(int result[2], const char symbol);
	void verticalMoveControl(int result[2], const char symbol);
	int gamePlayForComputer();// pve gameplay for singleplayer mode
	int gamePlayMultiComputer(); // pvp gameplay for multiplayer mode
	int gamePlayForMultiPlayer();// pve gameplay for multiplayer mode
	int isBoardFull() const; // checks board cells for empty cell
	int checkWinner(const char symbol); // checks winner according to the symbol
	int play(int column); // plays user move
	int play();	// plays computer move
	int gamePlayForPlayers(); // pvp gameplay for singleplayer mode
	string const takeInput();
	void saveGame(const string& userSequence, const string& fileName);
	void loadGame(const string& fileName);
	Cell **gameCells; // game board
	int width;
	int height;
	char gameMode; // keeps pvp or pve mode
	string userSequence; // indicates which user start game
	int playerTurn;	// keeps player turn during the game
	int gameStatus; // indicates game ending
	static int livingCell; // number of living cell
	static int gameOrder; // indicates which object start the game
};

int ConnectFour::livingCell = 0;
int ConnectFour::gameOrder = 1; // for multiplayer game


int main() {

	int flag = 1; // indicates all games are over
	int temp; // for object turn
	char singleOrMulti = ConnectFour::singlePlayerOrMultiPlayer();
	string boardFileName; // for games of multiplayer mode

	if (singleOrMulti == 'S' || singleOrMulti == 's') {
		ConnectFour game1;
		game1.playGame(); // singleplayer mode, just one call and game will be over
	}
	else if (singleOrMulti == 'M' || singleOrMulti == 'm') {
		// multiplayer mode
		cout << "Obje1: " << endl;
		boardFileName = ConnectFour::takeFileName(); // takes file name
		ConnectFour game1(boardFileName); // builds a board according to the file
		game1.setGameMode();  // sets game mode

		cout << "Obje2: " << endl;
		boardFileName = ConnectFour::takeFileName();
		ConnectFour game2(boardFileName);
		game2.setGameMode();  // sets game mode

		cout << "Obje3: " << endl;
		boardFileName = ConnectFour::takeFileName();
		ConnectFour game3(boardFileName);
		game3.setGameMode();

		cout << "Obje4: " << endl;
		boardFileName = ConnectFour::takeFileName();
		ConnectFour game4(boardFileName);
		game4.setGameMode();  // sets game mode

		cout << "Obje5: " << endl;
		boardFileName = ConnectFour::takeFileName();
		ConnectFour game5(boardFileName);
		game5.setGameMode();  // sets game mode

		// indicates games are not over
		// if all gameStatus value sets zero, the loop is ended
		game1.setGameStatus(1);
		game2.setGameStatus(1);
		game3.setGameStatus(1);
		game4.setGameStatus(1);
		game5.setGameStatus(1);

		while (flag == 1) {
			flag = 0;


			// If there is a game for play, takes another object number
			if (game1.getGameStatus() == 1 ||
				game2.getGameStatus() == 1 ||
				game3.getGameStatus() == 1 ||
				game4.getGameStatus() == 1 ||
				game5.getGameStatus() == 1)
			{
				do {
					cout << "Obje seciniz: ";
					cin >> temp;
					// end of file control
					if (cin.eof())
						return 0;
					if (cin.fail()) {
						cin.clear();
						cin.ignore();
					}
					// If the size of the board isnt between 4 and 20, it takes another input
					if (temp < 1 || temp > 5)
						cerr << "Invalid Object number, enter diffirent value:";
				} while (temp < 1 || temp > 5);

				ConnectFour::setGameOrder(temp); // sets which object is start
				flag = 1;
			}

			// start of gameplay for multiplayer mode
			// if flag returns 1, gameplay will continue
			if (ConnectFour::getGameOrder() == 1 && game1.getGameStatus() == 1)
				flag = game1.playGameForMulti("Obje1");
			else if (ConnectFour::getGameOrder() == 2 &&
				game2.getGameStatus() == 1)
				flag = game2.playGameForMulti("Obje2");
			else if (ConnectFour::getGameOrder() == 3 &&
				game3.getGameStatus() == 1)
				flag = game3.playGameForMulti("Obje3");
			else if (ConnectFour::getGameOrder() == 4 &&
				game4.getGameStatus() == 1)
				flag = game4.playGameForMulti("Obje4");
			else if (ConnectFour::getGameOrder() == 5 &&
				game5.getGameStatus() == 1)
				flag = game5.playGameForMulti("Obje5");
		}
	}

	return 0;
}


void ConnectFour::fileReader(string fileName) {
	ifstream inputStream;
	char temp; // character from file
	int i = 0, j = 0;
	int totalRow = 0; // for calculating board height
	int maxLength = 0;// for calculating board width
	int currentLength = 0;
	int totalCh = 1; // for loop control

	inputStream.open(fileName.c_str());

	inputStream.get(temp);
	while (!inputStream.eof())
	{
		// if there is an asterix, count length
		if (temp == '*')
			currentLength++;
		// if line over, check length of line(for width)
		else if (temp == '\n') {
			if (currentLength > maxLength)
				maxLength = currentLength;
			// row is incremented for calculation of height
			if (currentLength > 0)
				totalRow++;
			// resets line length for new line
			currentLength = 0;
		}
		inputStream.get(temp);
		totalCh++; // counting every character
		if (inputStream.eof()) {
			// compares line length for boaard width
			if (currentLength > maxLength)
				maxLength = currentLength;
			// if last line has character, increments height
			if (currentLength > 0)
				totalRow++;
		}
	}
	// assingning board height and width
	width = maxLength;
	height = totalRow;

	inputStream.close();

	// creating board according to the width and height
	gameCells = new Cell*[height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell[width];

	inputStream.open(fileName.c_str());
	// creating a temporary array
	char *boardArr = new char[totalCh + 1];
	inputStream.get(temp);

	// saves all characters to the temporary array
	i = 0;
	for (; !inputStream.eof() && totalCh + 1 > i; i++) {
		boardArr[i] = temp;
		inputStream.get(temp);
	}
	int last = i;

	inputStream.close();

	// fills board with empty character and dot character
	int a = 0, b = 0;
	for (i = 0; i < last; i++) {

		if (boardArr[i] == ' ') {
			gameCells[a][b] = Cell(' ', a, b, 1);
			b++;
		}
		else if (boardArr[i] == '*') {
			gameCells[a][b] = Cell('.', a, b, 1);
			b++;
		}
		else if (boardArr[i] == '\n') {
			while (b < width) {
				gameCells[a][b] = Cell(' ', a, b, 1);
				b++;
			}
			a++;
			b = 0;
		}
	}


	delete [] boardArr;
}

ConnectFour::~ConnectFour() {
	for(int i = 0; i < height; i++)
		delete [] gameCells[i];

	delete [] gameCells;
}

string const ConnectFour::takeFileName() {
	string txtName;
	ifstream inputStream;
	int len; // input length
	int inputValidity = 0; // checks validity of input

	cout << "Enter the file name: ";

	while (inputValidity == 0) {
		inputValidity = 1;

		cin >> txtName;
		len = txtName.length();
		// if length of input bigger than 4, checks validity
		if (len > 4) { // checks file name
			if (txtName.substr(len - 4, 4) != ".txt" &&
				txtName.substr(len - 4, 4) != ".TXT") {
				cerr << "Invalid input, please try again: 1111111";
				inputValidity = 0; // marks variable for loop
			}
		}
		else {
			cerr << "Invalid input, please try again: ";
			inputValidity = 0; // If there is an error, loop is continuing
		}

		if(inputValidity == 1) {
			// checks file opening, if there is an error takes another input
			inputStream.open(txtName.c_str());
			if(inputStream.fail()) {
				cerr << "Invalid input, please try again: ";
				inputValidity = 0;
			}
			inputStream.close();
		}
		
	}

	// returns name of file
	return txtName;
}

// compares two cell objects
bool ConnectFour::Cell::operator==(const ConnectFour::Cell &other) const {
	// if object's member variables are equal, returns true
	if (other.getCol() == getCol() && other.rowNumber == rowNumber &&
		other.cellValue == cellValue)
		return true;
	return false;
}

// constructs objects according to the file
ConnectFour::ConnectFour(const string& fileName) {
	ifstream inputStream;
	char temp; // keeps character from file
	int i = 0, j = 0;
	int totalRow = 0; // for calculating board height
	int maxLength = 0;// for calculating board width
	int currentLength = 0;
	int totalCh = 1; // for loop control

	inputStream.open(fileName.c_str());

	inputStream.get(temp);
	while (!inputStream.eof())
	{
		// if there is an asterix, count length
		if (temp == '*')
			currentLength++;
		// if line over, check length of line(for width)
		else if (temp == '\n') {
			if (currentLength > maxLength)
				maxLength = currentLength;
			// row is incremented for calculation of height
			if (currentLength > 0)
				totalRow++;
			// resets line length for new line
			currentLength = 0;
		}
		inputStream.get(temp);
		totalCh++; // counting every character
		if (inputStream.eof()) {
			// compares line length for boaard width
			if (currentLength > maxLength)
				maxLength = currentLength;
			// if last line has character, increments height
			if (currentLength > 0)
				totalRow++;
		}
	}
	// assingning board height and width
	width = maxLength;
	height = totalRow;

	inputStream.close();

	// creating board according to the width and height
	gameCells = new Cell*[height];
	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell[width];

	inputStream.open(fileName.c_str());
	// creating a temporary array
	char *boardArr = new char[totalCh + 1];
	inputStream.get(temp);

	// saves all characters to the temporary array
	i = 0;
	for (; !inputStream.eof() && totalCh + 1 > i; i++) {
		boardArr[i] = temp;
		inputStream.get(temp);
	}
	int last = i;

	inputStream.close();

	// fills board with empty character and dot character
	int a = 0, b = 0;
	for (i = 0; i < last; i++) {

		if (boardArr[i] == ' ') {
			gameCells[a][b] = Cell(' ', a, b, 1);
			b++;
		}
		else if (boardArr[i] == '*') {
			gameCells[a][b] = Cell('.', a, b, 1);
			b++;
		}
		else if (boardArr[i] == '\n') {
			while (b < width) {
				gameCells[a][b] = Cell(' ', a, b, 1);
				b++;
			}
			a++;
			b = 0;
		}
	}


	delete [] boardArr;
}

bool ConnectFour::operator ==(const ConnectFour& other) {
	// parametredeki objenin member degiskenleriyle base objenin degiskenleri
	// karsilastirilir
	if (other.width != width || other.height != height)
		return false;
	else if (other.gameMode != gameMode)
		return false;

	// oyun tahtasindaki her hucre karsilastirilir
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (other.gameCells[i][j].getCellValue() !=
				gameCells[i][j].getCellValue())
				return false;
	return true;
}

bool ConnectFour::operator !=(const ConnectFour& other) {
	// parametredeki objenin member degiskenleriyle base objenin degiskenleri
	// karsilastirilir
	if (other.width != width ||
		other.height != height ||
		other.gameMode != gameMode)
		return true;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (other.gameCells[i][j].getCellValue() !=
				gameCells[i][j].getCellValue())
				return true;
	return false;
}

ConnectFour::Cell ConnectFour::Cell::operator++() {
/* cell in sahipligi degistirilir. eger cell empty ise user1' gecer,
user1'se user2'ye, user2'yse computer'e gecer. */
	if (cellOwner == 1 || cellOwner == 2 || cellOwner == 3)
		cellOwner++;
	else if (cellOwner == 4)
		cellOwner = 1;
	// degiskenlere gore cell return edilir
	return Cell(cellValue, rowNumber, getCol(), cellOwner);
}

ConnectFour::Cell ConnectFour::Cell::operator++(int ignore) {
	char temp = cellOwner;

	if (cellOwner == 1 || cellOwner == 2 || cellOwner == 3)
		cellOwner++;
	else if (cellOwner == 4)
		cellOwner = 1;

	return Cell(cellValue, rowNumber, getCol(), temp);
}

int ConnectFour::playGameForMulti(string objectName) {
	int playAgain = 1;
	int temp;

	cout << "Game mode: " << gameMode << endl;
	if (gameStatus == 1) {
		cout << objectName << ":" << endl;
		while (playAgain == 1) {
			if (gameMode == 'p' || gameMode == 'P') // user1 vs user2
				playAgain = gamePlayForMultiPlayer();
			else if (gameMode == 'c' || gameMode == 'C')
				playAgain = gamePlayMultiComputer();
		}
	}

	return gameStatus;
}

int ConnectFour::gamePlayMultiComputer() {
	int user1 = 0;
	int computer = 0;
	int isFilled = 0;
	int winner = 0;
	int column;
	string input;
	int isSaved;

	if (userSequence == "user1")
		printBoard();

	do {
		cout << "Living Cell: " << ConnectFour::livingCell << endl;
		isSaved = 0;
		cout << "user's move: ";
		input = takeInput(); // getting move from user
		// if length is one, takes a move
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
		// eger dosya sonuysa fonksiyon bitirilir.
		else if (input == "eof")
			return 0;
		if (user1 == 0 && isFilled == 0 && isSaved == 0)
			cerr << "Invalid move, please try again" << endl;

		isFilled = isBoardFull();
	} while ((user1 == 0 && isFilled == 0) || isSaved == 1);

	ConnectFour::livingCellCounter();

	//if it is valid, makes move
	isFilled = isBoardFull(); // controls empty cells
	winner = checkWinner('X');
	printBoard();
	if (winner == 1) {
		cout << "Winner is user.\n";
		gameStatus = 0;
	}

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
		ConnectFour::livingCellCounter();
		winner = checkWinner('O');
		printBoard();
		if (winner == 2) {
			cout << "Winner is computer.\n";
			gameStatus = 0;
		}
	}


	// If there is no winner and board is filled, it is executed
	if (winner == 0 && isFilled == 1) {
		cout << "Nobody won the game.\n";
		gameStatus = 0;
	}

	cout << "Living Cell: " << ConnectFour::livingCell << endl;
	return 0;
}

int ConnectFour::gamePlayForMultiPlayer() {
	int user1 = 0; // for controlling move validity
	int user2 = 0;
	int winner = 0; // indicates winner of the game
	int isSaved = 0;
	int isFilled = 0; // all board is filling or not
	int row = height - 1; // coordinate of move
	int column; // coordinate of move
	string input;
	playerTurn = 0; // indicates player turn

	if (userSequence == "user1")
		printBoard();

	if (isFilled == 0 && userSequence != "user2")
		do {
			cout << "Living Cell: " << ConnectFour::livingCell << endl;
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

		playerTurn++; // indicates player turn
		ConnectFour::livingCellCounter(); // increament living cell
		winner = checkWinner('X'); // checks winner for user1
		printBoard();
		if (winner == 1) {
			cout << "Winner is user1.\n";
			gameStatus = 0;
		}

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
				ConnectFour::livingCellCounter();
				winner = checkWinner('O');
				printBoard();

				if (winner == 2) {
					cout << "Winner is user2.\n";
					gameStatus = 0;
				}
		}

		// If there is no winner and board is filled, it is executed
		if (winner == 0 && isFilled == 1) {
			cout << "Nobody won the game.\n";
			gameStatus = 0;
		}
		cout << "Living Cell: " << ConnectFour::livingCell << endl;
		return 0;
}


int ConnectFour::gamePlayForComputer() {
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
			cout << "Living Cell: " << ConnectFour::livingCell << endl;
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

		ConnectFour::livingCellCounter();

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
			ConnectFour::livingCellCounter();
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

int ConnectFour::isGameEnd() {
	// eger kazanan birisi varsa veya tahtanin tamami doluysa 1 return et
	if (checkWinner('X') || checkWinner('O') || isBoardFull())
		return 1;
	else
		return 0;
}

char ConnectFour::setGameMode() {
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

char ConnectFour::singlePlayerOrMultiPlayer() {
	int len;
	string choice;

	cout << "Choose multiplayer or singleplayer. (M) or (S): ";

	do {
		cin >> choice;
		len = choice.size();
		if ((choice[0] != 'M' && choice[0] != 'S' &&
			choice[0] != 'm' && choice[0] != 's') || len != 1)
			cerr << "Invalid choice. Please enter (M) or (S): ";

	} while ((choice[0] != 'M' && choice[0] != 'S' &&
		choice[0] != 'm' && choice[0] != 's') || len != 1);

	return choice[0];
}

void ConnectFour::playGame() {
	int playAgain = 1;

	// kullanicidan dosya ismini alir
	string boardFileName = ConnectFour::takeFileName();
	// dosyayi acar ve oyun tahtasini karakterlerle doldurur.
	fileReader(boardFileName);
	// oyun modunu ayarlar
	gameMode = setGameMode();

	while (playAgain == 1) {
		if (gameMode == 'p' || gameMode == 'P') // user1 vs user2
			playAgain = gamePlayForPlayers();
		else if (gameMode == 'c' || gameMode == 'C') // user1 vs computer
			playAgain = gamePlayForComputer();
	}
}

int ConnectFour::gamePlayForPlayers()
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
				cout << "Living Cell: " << ConnectFour::livingCell << endl;
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
			ConnectFour::livingCellCounter();
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
					ConnectFour::livingCellCounter();
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

int ConnectFour::play(int column) {
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


int ConnectFour::play() {
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

void ConnectFour::verticalMoveControl(int result[2], char symbol) {
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

void ConnectFour::horizontalMoveControl(int result[2], char symbol) {
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

ConnectFour::ConnectFour() :width(5), height(5) {
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

ConnectFour::ConnectFour(int heightValue, int widthValue)
	: width(widthValue), height(heightValue)
{
	gameCells = new Cell*[height];

	for (int i = 0; i < height; i++)
		gameCells[i] = new Cell[width];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			gameCells[i][j] = Cell('.', i, j, 1);
}

void ConnectFour::resizeTheBoard(int heightValue, int widthValue)
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

int ConnectFour::checkWinner(char symbol)
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

int ConnectFour::isBoardFull() const
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

string const ConnectFour::takeInput() {
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
		if(inputValidity == 1 && ( input == "LOAD" || input == "load" )) {
			inputStream.open(txtName.c_str());
			if(inputStream.fail()) {
				cerr << "Invalid input, please try again: ";
				inputValidity = 0; //eger dosya acilmiyorsa baska bir dosya alir.
			}
			inputStream.close();
		}
		// eger save yapilan dosyadan bir sorun varsa baska bir dosya ismi
		// alinir
		else if(inputValidity == 1 && ( input == "SAVE" || input == "save" )) {
			outputStream.open(txtName.c_str());
			if(outputStream.fail()) {
				cerr << "Invalid input, please try again: ";
				inputValidity = 0;
			}
			outputStream.close();
		}

	}

	return result;
}

void ConnectFour::saveGame(const string& userSequence, const string& fileName) {
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

void ConnectFour::loadGame(const string& fileName) {
	ifstream inStream;
	char temp;
	int cellNumber;
	int totalCell = ConnectFour::livingCell;
	int currentCell = 0;
	int heightValue;
	int widthValue;

	inStream.open(fileName.c_str()); // opening file

	// count livingCell
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			if (gameCells[j][i].getCellValue() == 'O' ||
				gameCells[j][i].getCellValue() == 'X')
				currentCell++;
		}

	if(currentCell % 2 == 1)
		currentCell++;
	// takes data from file
	inStream >> cellNumber >> heightValue >> widthValue 
			 >> userSequence >> gameMode;


	// set living cell number
	totalCell += cellNumber;
	totalCell -= currentCell;
	ConnectFour::setLivingCell(totalCell);

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
			if(temp == '.')
				gameCells[i][j++] = Cell(temp, i, j, 1);
			else if(temp == 'X')
				gameCells[i][j++] = Cell(temp, i, j, 2);
			else if(temp == 'O' &&  (gameMode == 'p' || gameMode == 'P'))
				gameCells[i][j++] = Cell(temp, i, j, 3);
			else if(temp == 'O' &&  (gameMode == 'c' || gameMode == 'C'))
				gameCells[i][j++] = Cell(temp, i, j, 4);
			else		
				gameCells[i][j++].setCell(temp);	
		}
	}

	inStream.close();
}

ConnectFour::Cell::Cell(char ch, int row, int column, int owner) {
	cellValue = ch;
	rowNumber = row + 1;
	position = 'A' + column;
	cellOwner = owner;
}

ConnectFour::Cell::Cell() {}

void ConnectFour::printBoard() const
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

void ConnectFour::getSize() {
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
