/*>>>>>>>>>>>>>>>>>>>>>>>>>>>   HW2   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 * Homework-2
 *
 * Author: Islam Goktan SELCUK
 * No: 141044071
 *
 *   Program is the game of Connect Four. Game has two gameplay mode.
 *     They are user versus user and computer versus user.
 */
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int getSize();
// It takes size of the board and controls validity of size.

char gameMode();
/* Takes gameplay mode to user. According to user's choice game starts
 computer vs user mode or user vs user mode.
*/

void verticalMoveControl(char board[][20], int size,
						 int result[2], char symbol);
// Checks the vertical symbols for intelligent move
// result[0] : target place for move
// result[1] : numbers of symbols side by side

void horizontalMoveControl(char board[][20], int size,
						   int result[2], char symbol);
// Checks the horizontal symbols for intelligent move
// result[0] : target place for move
// result[1] : numbers of symbols side by side


//>>>>>>>>>>>>>>>>> HW-2 UPDATED FUNCTİONS <<<<<<<<<<<<<<<<<<<<<

void initialize(char board[][20], int size = 4);
// board array is game board and size is board size which is user's choice
// It creates a game board according to the size variable.

int userMove(char board[][20], const int& column, int row, char symbol);
/* symbol parameter: It represents character 'O' or 'X'.
   column and row parameters: They represent place for symbol in the board.
 According to the row and the column function writes character symbol in the
 board.
*/

int computerMove(char board[][20], const int& size);
/* It produces intelligent move for computer. */

void printBoard(char board[][20], int size = 4);
// Prints board according to the variables.

void printLetter(int size = 4);
// Prints letters on top of the board according to the size of the board.

int isBoardFull(char board[][20], const int& size);
// It controls whether every cell is filled in the board.
// If board has empty cell returns 0, otherwise returns 1;

int checkWinner(char board[][20], const int& size, const char symbol);
/* It checks whether there is a winner.
 It controls parameter symbol in the board. If it finds any four of them
 returns 1 for symbol 'O' or 2 for symbol 'X' and makes symbols lowercase
 letter. İf cant find winner, it returns 0.
*/

int gamePlay(char board[][20], int& size, char& gameMode, string& userOrder);
/* It has user1 versus user2 gameplay mode. It takes moves respectively from
 users and it checks the users every move for finding winner.
 Finally returns winner of the game.
*/

int gamePlayForComputer(char board[][20], int& size,
						 char& gameMode, string& userOrder);
/* It has computer versus user gameplay mode. It takes moves respectively from
 user and computer. I used srand and rand function for computer moves.
 Function checks the players every move for finding winner.
 Finally returns winner of the game.
*/

//>>>>>>>>>>>>>>>>> HW-2 NEW FUNCTİONS <<<<<<<<<<<<<<<<<<<<<

void loadGame(char board[][20], int& size,
              string& userSequence,
              char& gameMode,
              const string fileName);
/*  It loads game according to file name.
	size: size of board
	userSequence: which player going to make move
	gameMode: user vs user or computer vs user
	fileName: file which is loaded
*/


void saveGame(char board[][20], const int size,
              const string userSequence,
              const char gameMode,
              string fileName);
/*  It saves game according to file name.
	size: size of board
	userSequence: which player going to make move
	gameMode: user vs user or computer vs user
	fileName: file which is going to save
*/


string checkInput(int size = 4);
// It checks users moves and if user enter the save or load word, checks
// validity of these words.

int main() {
    char board[20][20] = {};
    char choice = 'p'; // game mode
    auto playAgain = 1; // If any game is loaded, loop is continuing
    decltype(playAgain) size; // board size
    string user = ""; // for user sequence

    size = getSize();
    choice = gameMode();	// for gameplay mode
    initialize(board, size);
    printBoard(board, size);

    while(playAgain == 1) {
        if (choice == 'p' || choice == 'P')    // user1 vs user2
            playAgain = gamePlay(board, size, choice, user);
        else if (choice == 'c' || choice == 'C')    // computer vs user
            playAgain = gamePlayForComputer(board, size, choice, user);
    }

    return 0;
}

string checkInput(int size) {
    string input;
    string txtName; // name of txt file
    char letter;	// for move control
    int len;		// length of input
    string result;
    int inputValidity = 0;

	// If input value isnt valid, takes another input.
    while(inputValidity == 0) {
        cin >> input;
        letter = input[0]; // for users move
        inputValidity = 1; // If there is no error, it breaks loop

        if(input == "SAVE" || input == "save" ||
           input == "LOAD" || input == "load") {
            cin >> txtName; // If save or load is read, takes file name
            len = txtName.length();
            if(len > 4) // checks file name
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
        else if(input.length() == 1) { // checks validity of users move
            if(letter >= 'A' && letter <= 'Z')
                letter += 'a' - 'A';
            if( letter > ( size - 1 + 'a') || letter < 'a' ) {
                cerr << "Invalid input, please try again: ";
                inputValidity = 0;
            }
            else
                result = letter;

        }
        else {
            cerr << "Invalid input, please try again: ";
            inputValidity = 0;
        }
    }

    return result;
}

void loadGame(char board[][20], int& size,
              string& userSequence,
              char& gameMode,
              const string fileName) {

    ifstream inStream;
    char temp;

    inStream.open(fileName.c_str()); // opening file
    if(inStream.fail()) {
        cerr << "Input file opening failed." << endl;
        exit(1);
    }

	// takes data from file
    inStream >> size >> userSequence >> gameMode;

	// reads all board cell
    for(int j = 0; j < size; j++)
        for(int i = 0; i < size; i++) {
            inStream >> temp;
            board[j][i] = temp;
        }

    inStream.close();
}

void saveGame(char board[][20], const int size,
              const string userSequence,
              const char gameMode,
              string fileName) {

    ofstream outStream;

    outStream.open(fileName.c_str()); // opening or creating file
    if(outStream.fail()) { // if there is an error, prints error
        cerr << "Output file openning failed." << endl;
        exit(1);
    }

	// writes data to file
    outStream << size << endl
              << userSequence << endl
              << gameMode << endl;

	// writes all board to file
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            outStream << board[i][j];
        outStream << endl;
    }

    outStream.close();
}


int getSize() {

    int size; // size of the board
    cout << "Enter size of the board. Enter n for nXn board:  ";

    do {
    	cin >> size;
    	if(cin.fail()) {
    		cin.clear();
    		cin.ignore();
    	}
	// If the size of the board isnt between 4 and 20, it takes another input
    	if(size < 4 || size > 20 || size % 2 == 1)
    		cerr << "Invalid board size, enter a diffirent value: ";
    } while(size < 4 || size > 20 || size % 2 == 1);

    return size;
}

void initialize(char board[][20], int size) {
    cout << endl;
    // every cell in the board is assigned a dot character
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = '.';
}

void printBoard(char board[][20], int size) {
    printLetter(size); // prints letters top of the board

    // prints every cell in the board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }

    cout << endl;
}

void printLetter(int size) {
    char letter = 'a';

    // prints letters top of the board according to the size
    for (int i = 'a'; i < 'a' + size && letter <= 'z'; i++) {
        cout << letter << " ";
        letter++;
    }
    cout << endl;
}

char gameMode() {
    char choice = 0;

    cout << "Choose game mode:\n"
         << "Enter (P) for two player game.(user versus user)\n"
         << "Enter (C) for computer versus user game: ";
    do {
        cin >> choice;
        if(choice != 'P' && choice != 'C' && choice != 'p' && choice != 'c')
            cerr << "Invalid choice. Please enter P or C : ";
    } while(choice != 'P' && choice != 'C' && choice != 'p' && choice != 'c');

    return choice;
}


int userMove(char board[][20], const int& column, int row, char symbol) {
    // If desired row is filled by users or computer, row is reduced.
    //>>>>>>Row always initializes to row = size-1 in gameplay function.<<<<<
    while((board[row][column] == 'O' || board[row][column] == 'X') && row >= 0)
        row--;

    // If there is no row for move return 0
    if(row == -1)
        return 0; // It means invalid move
    else { // // If move is valid, symbol('O' or 'X') is written.
        board[row][column] = symbol;
        return 1; // It means valid move
    }
}

int gamePlay(char board[][20], int& size, char& gameMode, string& userOrder) {
    int user1 = 0; // for controlling move validity
    int user2 = 0;
    int isFilled = 0; // all board is filling or not
    int winner = 0; // indicates winner of the game
    int column; // coordinate of move
    int row = size - 1; // coordinate of move
    string input;
    int isSaved = 0;


    if(userOrder == "user1")
        printBoard(board, size);

    // continues as long as there is no winner or there is an empty cell in
    // the board
    while(isFilled == 0 && winner == 0) {
        isFilled = isBoardFull(board, size); // controls empty cells

        if(isFilled == 0 && userOrder != "user2")
            do {
                isSaved = 0;
                cout << "user1's move: ";
                input = checkInput(size); // getting move from user1
                if (input.length() == 1) {
                    column = input[0] - 'a';
                    user1 = userMove(board, column, row, 'X');// makes move
                } else if (input.substr(0, 4) == "save" ||
                           input.substr(0, 4) == "SAVE") {
                    saveGame(board, size, "user1", 'P', input.substr(4));
                    isSaved = 1;
                }

                else if(input.substr(0, 4) == "load" ||
                        input.substr(0, 4) == "LOAD") {
                    loadGame(board, size, userOrder, gameMode, input.substr(4));
                    return 1;

                }
                if(user1 == 0 && isFilled == 0 && isSaved == 0)
                    cerr << "Invalid move, please try again" << endl;

                isFilled = isBoardFull(board, size);
            } while ((user1 == 0 && isFilled == 0) || isSaved == 1);

        winner = checkWinner(board, size, 'X'); // checks winner for user1
        printBoard(board, size);
        if(winner == 1)
            cout << "Winner is user1.\n";

        // if user1 is not winner, user2 makes move
        if(winner == 0) {
            if(userOrder == "user2")
                userOrder = "none";
            isFilled = isBoardFull(board, size);
            if(isFilled == 0)
                do {
                    isSaved = 0;
                    cout << "user2's move: ";
                    input = checkInput(size); // getting move from user1
                    if(input.length() == 1) {
                        column = input[0] - 'a';
                        user2 = userMove(board, column, row, 'O');// makes move
                    }
                    else if(input.substr(0, 4) == "save" ||
                            input.substr(0, 4) == "SAVE") {

                        saveGame(board, size, "user2", 'P', input.substr(4));
                        isSaved = 1;
                    }

                    else if(input.substr(0, 4) == "load" ||
                            input.substr(0, 4) == "LOAD") {

                        loadGame(board, size, userOrder, gameMode,
                        		 input.substr(4));
                        return 1;
                    }

                    if(user2 == 0 && isFilled == 0 && isSaved == 0)
                        cerr << "Invalid move, please try again" << endl;

                    isFilled = isBoardFull(board, size);
                } while ((user2 == 0 && isFilled == 0) || isSaved == 1);
            winner = checkWinner(board, size, 'O');
            printBoard(board, size);
            if(winner == 2)
                cout << "Winner is user2.\n";
        }
    }
    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1)
        cout << "Nobody won the game.\n";

    return 0;
}

int gamePlayForComputer(char board[][20], int& size,
						 char& gameMode, string& userOrder) {
    int user1 = 0;
    int computer = 0;
    int isFilled = 0;
    int winner = 0;
    int column;
    int row = size - 1;
    char letter;
    string input;
    int isSaved;

    if(userOrder == "user1")
        printBoard(board, size);
    while(isFilled == 0 && winner == 0) {
        do {
            isSaved = 0;
            cout << "user's move: ";
            input = checkInput(size); // getting move from user1
            if (input.length() == 1) {
                column = input[0] - 'a';
                user1 = userMove(board, column, row, 'X');// makes move
            } else if (input.substr(0, 4) == "save" ||
                       input.substr(0, 4) == "SAVE") {
                saveGame(board, size, "user1", 'C', input.substr(4));
                isSaved = 1;
            }

            else if(input.substr(0, 4) == "load" ||
                    input.substr(0, 4) == "LOAD") {
                loadGame(board, size, userOrder, gameMode, input.substr(4));
                return 1;

            }
            if(user1 == 0 && isFilled == 0 && isSaved == 0)
                cerr << "Invalid move, please try again" << endl;

            isFilled = isBoardFull(board, size);
        } while ((user1 == 0 && isFilled == 0) || isSaved == 1);
        //if it is valid, makes move
        isFilled = isBoardFull(board, size); // controls empty cells
        winner = checkWinner(board, size, 'X');
        printBoard(board, size);
        if(winner == 1)
            cout << "Winner is user.\n";

        // if user isnt winner, computer makes move
        if(winner == 0) {
            cout << "computer's move: ";
            column = computerMove(board, size);
            // for seeing computer move
            letter = static_cast<char>('a' + column);
            cout << letter << endl;
            //if it is valid, makes move
            computer = userMove(board, column, row, 'O');
            isFilled = isBoardFull(board, size);
            // if move isnt valid, takes another move
            while (computer == 0 && isFilled == 0) {
                column = computerMove(board, size);
                computer = userMove(board, column, row, 'O');
                isFilled = isBoardFull(board, size);
            }
            winner = checkWinner(board, size, 'O');
            printBoard(board, size);
            if(winner == 2)
                cout << "Winner is computer.\n";
        }
    }

    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1)
        cout << "Nobody won the game.\n";

    return 0;
}


int computerMove(char board[][20], const int& size) {
    // data for winning moves
    int hor[2] = {}; 		// takes result from functions
    int ver[2] = {};
    // data for prevention moves
    int preventHor[2] = {};
    int preventVer[2] = {};

    int result = 0; // target place for move
    int found = 0;


    // prevention moves for user
    verticalMoveControl(board, size, preventVer, 'X');
    horizontalMoveControl(board, size, preventHor, 'X');

    // winning moves
    verticalMoveControl(board, size, ver, 'O');
    horizontalMoveControl(board, size, hor, 'O');

    // makes the most logical move
    // checks number of symbols side by side or over and over
    if(ver[1] > hor[1])
        result = ver[0];
    else
        result = hor[0];

	// If winning or losing is close, makes that moves
    if(ver[1] == 3)
        result = ver[0];
    else if(hor[1] == 3)
        result = hor[0];
    else if(preventHor[1] >= 2)
        result = preventHor[0];
    else if(preventVer[1] >= 2)
        result = preventVer[0];

	// there is no logical move then it finds first empty cell
    if(result == 0)
        for(int i = 0; i < size && found == 0; i++)
        	for(int j = 0; j < size && found == 0; j++)
        		if(board[i][j] == '.') {
        			result = j;
        			found = 1;
        		}

    return result; // target place
}

void verticalMoveControl(char board[][20], int size,
						 int result[2], char symbol) {
    int counter = 0; // keeps number of symbols over and over
    int max = 0;	 // max number of symbols
    int i, j;
	int lastIndex;

    // bottom to up
    for(j = 0; j < size; j++) {
        for(i = size - 1; i >= 0; i--) {
        	// counts number of symbols
            if (board[i][j] == symbol)
                counter++;
            // If there isnt computer symbol, starts counting again
            else if(board[i][j] != symbol) {
                lastIndex = i;
                // If maximum number is found and there is a empty cell,
                // place is assigned to result
                if(counter > max && board[lastIndex][j] == '.') {
                    max = counter;
                    result[0] = j;
                }
                counter = 0;
            }
        }
    }
    result[1] = max; // maximum number of symbols
}

void horizontalMoveControl(char board[][20], int size,
							 int result[2], char symbol) {
    int counter = 0;
    int max = 0;
    int y = 0; // place for move
    int i, j, a, k; // counters
    char temp[4] = {}; // It keeps every side by side 4 cells in the board

    result[0] = 0;
    // left to right
    for(k = size - 1; k >= 0; k--) {
        for (i = 0; i <= size - 4; i++) {
            for (j = i, a = 0; a < 4; j++, a++)
                temp[a] = board[k][j]; // four cells from board

            counter = 0;
            for (a = 0; a < 4 && counter != -1; a++) {
                if (temp[a] == symbol) // counting symbols
                    counter++;
                // If there is a opponent symbol, stops counting
                else if ( (symbol == 'X' && temp[a] == 'O') ||
                (symbol == 'O' && temp[a] == 'X') )
                    counter = -1;
            }
            if (counter > max) {
                for(int b = 0, y = j - 4; b < 4; b++, y++)
                // If there is a empty cell and down of the cell is filled,
                // assigns place for move
                    if (board[k + 1][y] != '.' || k + 1 == size)
                        if (board[k][y] == '.') {
                            result[0] = y;
                            max = counter;
                        }
            }
        }
    }

    result[1] = max;
}

int isBoardFull(char board[][20], const int& size) {
    int result = 1;
    // It scans every cell in the board
    for(int i = 0; i < size && result == 1; i++)
        for(int j = 0; j < size && result == 1; j++)
            if(board[i][j] == '.')
                result = 0;

    // If there is an empty cell returns 0, otherwise returns 1
    return result;
}

int checkWinner(char board[][20], const int& size, const char symbol) {
    int result = 0;
    int i, j;
    char lowerCase =  symbol + ('a' - 'A'); // converts letter to lowercase

    // It controls every cell in the board for finding four same symbols
    for( i = 0; i < size && result == 0; i++)
        for( j = 0; j < size && result == 0; j++) {
            // controls from bottom to up
            if (i >= 3 &&
                board[i][j] == symbol &&
                board[i - 1][j] == symbol &&
                board[i - 2][j] == symbol &&
                board[i - 3][j] == symbol) {
                for (int a = 0; a < 4; a++) // converts letters to lowercase
                    board[i - a][j] = lowerCase;

                result = 1;
            }
                // controls from left to right
            else if (j <= size - 4 &&
                     board[i][j] == symbol &&
                     board[i][j + 1] == symbol &&
                     board[i][j + 2] == symbol &&
                     board[i][j + 3] == symbol) {
                for (int a = 0; a < 4; a++)
                    board[i][j + a] = lowerCase;

                result = 1;
            }
                // controls left diagonal
            else if (i >= 3 && j >= 3 &&
                     board[i][j] == symbol &&
                     board[i - 1][j - 1] == symbol &&
                     board[i - 2][j - 2] == symbol &&
                     board[i - 3][j - 3] == symbol) {
                for (int a = 0; a < 4; a++)
                    board[i - a][j - a] = lowerCase;

                result = 1;
            }
                // controls right diagonal
            else if (i >= 3 && j <= size - 4 &&
                     board[i][j] == symbol &&
                     board[i - 1][j + 1] == symbol &&
                     board[i - 2][j + 2] == symbol &&
                     board[i - 3][j + 3] == symbol) {
                for (int a = 0; a < 4; a++)
                    board[i - a][j + a] = lowerCase;

                result = 1;
            }
        }

    // for symbol 'O' it returns 2 and for symbol 'X' it returns 1
    // because the winner is determined by this data
    if(result == 1 && symbol == 'O')
        return 2;

    return result;
}
