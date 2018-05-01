/*>>>>>>>>>>>>>>>>>>>> HW-3 Connect Four with Classes <<<<<<<<<<<<<<<<<<<<<\\
 * Homework-3
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
	// initiliazies height and width of board according to the parameters
    ConnectFour(int heightValue, int widthValue);
    ConnectFour(int size); // initializes square board
    ConnectFour();
    inline const int getWidth() const { return width; }; 
    inline const int getHeight() const { return height; };
    inline const string getUserSequence() const { return userSequence; };
    inline const char  getGameMode() const { return gameMode; }; // pvp or pve
    char setGameMode();
    void printBoard() const;
    void loadGame(const string fileName);
    void saveGame(const string userSequence, const string fileName);
    string takeInput();
    int isBoardFull() const; // checks board cells for empty cell
    int checkWinner(const char symbol); // checks winner according to the symbol
    int play(int column); // plays user move
    int play();	// plays computer move
    int gamePlayForPlayers(); // pvp gameplay for singleplayer mode
    int gamePlayForComputer();// pve gameplay for singleplayer mode
    // initializes board size 
    void resizeTheBoard(const int heightValue, const int widthValue);
    // for intelligent move and game compare
    void horizontalMoveControl(int result[2], const char symbol);
    void verticalMoveControl(int result[2], const char symbol);
    // helps for player turn
    inline int getPlayerTurn() const { return playerTurn; };
    int isGameEnd();
    inline static const int totalLivingCell() { return livingCell; };
    inline static int livingCellCounter() { return ++livingCell; }; 
    inline static int setLivingCell(int temp) { livingCell = temp; };
    // returns turn of game objects
    inline static int getGameOrder() { return gameOrder; };
    // sets turn of game objects
    inline static void setGameOrder(int temp) { gameOrder = temp; };
    // for user interface, indicates which game is start
    static char singlePlayerOrMultiPlayer();
    void getSize(); // size of board, width and height
    int gamePlayMultiComputer(); // pvp gameplay for multiplayer mode
    int gamePlayForMultiPlayer();// pve gameplay for multiplayer mode
    void playGame(); // it plays game until the end for singleplayer mode
    // it plays game until the end for multiplayer mode
    int playGameForMulti(string objectName);
    // set game ending status
    inline void setGameStatus(int temp) { gameStatus = temp; };
    inline int getGameStatus() { return gameStatus; };
    // compare two games for user
    bool compareGame(ConnectFour otherGame);
private:
    class Cell {
    public:
        Cell(char ch, int row, int column);
        Cell();
        void printCellValues(); // for single cell
        inline char getCellValue() const { return cellValue; };
        inline void setCell(char ch) { cellValue = ch; };
        inline void output() const { cout << cellValue; };
    private:
        char position; // indicates column of board
        int rowNumber;
        char cellValue; // inside of cell
    };

    vector< vector<Cell> > gameCells; // game board
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
int ConnectFour::gameOrder = 1;

int main() {
    ConnectFour game1, game2, game3, game4, game5;    
    int flag = 1; // indicates all games are over
    int temp; // for object turn

    char singleOrMulti = ConnectFour::singlePlayerOrMultiPlayer();

    if(singleOrMulti == 'S' || singleOrMulti == 's') 
        game1.playGame(); // singleplayer mode
    else if(singleOrMulti == 'M' || singleOrMulti == 'm') {
    // multiplayer mode
        cout << "Obje1: " << endl;
        game1.getSize(); // gets size of board
        // sets size of board
        game1.resizeTheBoard(game1.getHeight(), game1.getWidth());
        game1.setGameMode();  // sets game mode

        cout << "Obje2: " << endl;
        game2.getSize();
        game2.resizeTheBoard(game2.getHeight(), game2.getWidth());
        game2.setGameMode();

        cout << "Obje3: " << endl;
        game3.getSize();
        game3.resizeTheBoard(game3.getHeight(), game3.getWidth());
        game3.setGameMode();

        cout << "Obje4: " << endl;
        game4.getSize();
        game4.resizeTheBoard(game4.getHeight(), game4.getWidth());
        game4.setGameMode();

        cout << "Obje5: " << endl;
        game5.getSize();
        game5.resizeTheBoard(game5.getHeight(), game5.getWidth());
        game5.setGameMode();

		// indicates games are not over
		// if all gameStatus value sets zero, the loop is ended
        game1.setGameStatus(1);
        game2.setGameStatus(1);
        game3.setGameStatus(1);
        game4.setGameStatus(1);
        game5.setGameStatus(1);

        while(flag == 1) {
            flag = 0;
            if(ConnectFour::getGameOrder() == 1 && game1.getGameStatus() == 1)
                flag = game1.playGameForMulti("Obje1");
            else if(ConnectFour::getGameOrder() == 2 &&
             game2.getGameStatus() == 1)
                flag = game2.playGameForMulti("Obje2");
            else if(ConnectFour::getGameOrder() == 3 &&
             game3.getGameStatus() == 1)
                flag = game3.playGameForMulti("Obje3");
            else if(ConnectFour::getGameOrder() == 4 &&
             game4.getGameStatus() == 1)
                flag = game4.playGameForMulti("Obje4");
            else if(ConnectFour::getGameOrder() == 5 &&
             game5.getGameStatus() == 1)
                flag = game5.playGameForMulti("Obje5");

	// If there is a game for play, takes another object number
            if(game1.getGameStatus() == 1 ||
               game2.getGameStatus() == 1 ||
               game3.getGameStatus() == 1 ||
               game4.getGameStatus() == 1 ||
               game5.getGameStatus() == 1) 
            {
                do {
                    cout << "Obje seciniz: ";
                    cin >> temp;
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore();
                    }
    // If the size of the board isnt between 4 and 20, it takes another input
                    if(temp < 1 || temp > 5)
                        cerr << "Invalid Object number, enter diffirent value:";
                } while(temp < 1 || temp > 5);

                ConnectFour::setGameOrder(temp); // sets which object is start
                flag = 1;
            }
        }    
    }

    return 0;
}


int ConnectFour::playGameForMulti(string objectName) {
	int playAgain = 1;
	int temp;

    cout << "Game mode: " << gameMode << endl;
	if(gameStatus == 1){
		cout << objectName << ":" << endl;
		while(playAgain == 1) {
	        if(gameMode == 'p' || gameMode == 'P') // user1 vs user2
	        	playAgain = gamePlayForMultiPlayer();
	        else if(gameMode == 'c' || gameMode == 'C')
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

    if(userSequence == "user1")
        printBoard();
    
    do {
        cout << "Living Cell: " << ConnectFour::livingCell << endl;
        isSaved = 0;
        cout << "user's move: ";
        input = takeInput(); // getting move from user
        if (input.length() == 1) {
            column = input[0] - 'a';
            user1 = play(column);// makes move
        } else if (input.substr(0, 4) == "save" ||
                   input.substr(0, 4) == "SAVE") {
            saveGame("user1", input.substr(4));
            isSaved = 1;
        }

        else if(input.substr(0, 4) == "load" ||
                input.substr(0, 4) == "LOAD") {
            loadGame(input.substr(4));
            return 1;

        }
        if(user1 == 0 && isFilled == 0 && isSaved == 0)
            cerr << "Invalid move, please try again" << endl;

        isFilled = isBoardFull();
    } while ((user1 == 0 && isFilled == 0) || isSaved == 1);

    ConnectFour::livingCellCounter();

    //if it is valid, makes move
    isFilled = isBoardFull(); // controls empty cells
    winner = checkWinner('X');
    printBoard();
    if(winner == 1){
        cout << "Winner is user.\n";
        gameStatus = 0;
    }

    // if user isnt winner, computer makes move
    if(winner == 0) {
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
        if(winner == 2) {
            cout << "Winner is computer.\n";
            gameStatus = 0;
        }
    }


    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1){
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
    playerTurn = 0;

    if(userSequence == "user1")
        printBoard();

    if(isFilled == 0 && userSequence != "user2")
        do {
            cout << "Living Cell: " << ConnectFour::livingCell << endl;
            isSaved = 0;
            cout << "user1's move: ";
            input = takeInput(); // getting move from user1
            if (input.length() == 1) {
                column = input[0] - 'a';
                user1 = play(column); // makes move

            } else if (input.substr(0, 4) == "save" ||
                       input.substr(0, 4) == "SAVE") {
                saveGame("user1", input.substr(4));
                isSaved = 1;
            }
            else if(input.substr(0, 4) == "load" ||
                    input.substr(0, 4) == "LOAD") {
                loadGame(input.substr(4));
                return 1;

            }
            if(user1 == 0 && isFilled == 0 && isSaved == 0)
                cerr << "Invalid move, please try again" << endl;

            isFilled = isBoardFull();
        } while ((user1 == 0 && isFilled == 0) || isSaved == 1);

    playerTurn++;
    ConnectFour::livingCellCounter();
    winner = checkWinner('X'); // checks winner for user1
    printBoard();
    if(winner == 1) {
        cout << "Winner is user1.\n";
        gameStatus = 0; 
    }

    // if user1 is not winner, user2 makes move
    if(winner == 0) {
        if(userSequence == "user2")
            userSequence = "none";
        isFilled = isBoardFull();
        if(isFilled == 0)
            do {
                isSaved = 0;
                cout << "user2's move: ";
                input = takeInput(); // getting move from user1
                if(input.length() == 1) {
                    column = input[0] - 'a';
                    user2 = play(column);// makes move
                }
                else if(input.substr(0, 4) == "save" ||
                        input.substr(0, 4) == "SAVE") {

                    saveGame("user2", input.substr(4));
                    isSaved = 1;
                }

                else if(input.substr(0, 4) == "load" ||
                        input.substr(0, 4) == "LOAD") {

                    loadGame(input.substr(4));
                    return 1;
                }

                if(user2 == 0 && isFilled == 0 && isSaved == 0)
                    cerr << "Invalid move, please try again" << endl;

                isFilled = isBoardFull();
            } while ((user2 == 0 && isFilled == 0) || isSaved == 1);
        playerTurn++;
        ConnectFour::livingCellCounter();
        winner = checkWinner('O');
        printBoard();

        if(winner == 2) {
            cout << "Winner is user2.\n";
            gameStatus = 0;
        }
    }
    
    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1) {
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

    if(userSequence == "user1")
        printBoard();
    while(isFilled == 0 && winner == 0) {
        do {
            cout << "Living Cell: " << ConnectFour::livingCell << endl;
            isSaved = 0;
            cout << "user's move: ";
            input = takeInput(); // getting move from user
            if (input.length() == 1) {
                column = input[0] - 'a';
                user1 = play(column);// makes move
            } else if (input.substr(0, 4) == "save" ||
                       input.substr(0, 4) == "SAVE") {
                saveGame("user1", input.substr(4));
                isSaved = 1;
            }

            else if(input.substr(0, 4) == "load" ||
                    input.substr(0, 4) == "LOAD") {
                loadGame(input.substr(4));
                return 1;

            }
            if(user1 == 0 && isFilled == 0 && isSaved == 0)
                cerr << "Invalid move, please try again" << endl;

            isFilled = isBoardFull();
        } while ((user1 == 0 && isFilled == 0) || isSaved == 1);

        ConnectFour::livingCellCounter();

        //if it is valid, makes move
        isFilled = isBoardFull(); // controls empty cells
        winner = checkWinner('X');
        printBoard();
        if(winner == 1)
            cout << "Winner is user.\n";

        // if user isnt winner, computer makes move
        if(winner == 0) {
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
            if(winner == 2)
                cout << "Winner is computer.\n";
        }
    }

    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1)
        cout << "Nobody won the game.\n";

    return 0;
}

int ConnectFour::isGameEnd() {
    if(checkWinner('X') || checkWinner('O') || isBoardFull()) 
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
        if((choice[0] != 'P' && choice[0] != 'C' &&
           choice[0] != 'p' && choice[0] != 'c') || len != 1)
            cerr << "Invalid choice. Please enter P or C : ";
    
    } while((choice[0] != 'P' && choice[0] != 'C' &&
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
        if((choice[0] != 'M' && choice[0] != 'S' &&
           choice[0] != 'm' && choice[0] != 's') || len != 1)
            cerr << "Invalid choice. Please enter (M) or (S): ";
    
    } while((choice[0] != 'M' && choice[0] != 'S' &&
            choice[0] != 'm' && choice[0] != 's') || len != 1);

    return choice[0];
}

void ConnectFour::playGame() {
    int playAgain = 1;

    getSize();
    resizeTheBoard(height, width);
    gameMode = setGameMode();

    while(playAgain == 1) {
        if(gameMode == 'p' || gameMode == 'P') // user1 vs user2
            playAgain = gamePlayForPlayers();
        else if(gameMode == 'c' || gameMode == 'C')
            playAgain = gamePlayForComputer();
    }
}

ConnectFour::ConnectFour(int size) 
    : width(size), height(size)
{

    for(int i = 0; i < size; i++)
        gameCells.push_back(vector<Cell>());

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            gameCells[i].push_back(Cell('.', i, j));
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

    if(userSequence == "user1")
        printBoard();

    // continues as long as there is no winner or there is an empty cell in
    // the board
    while(isFilled == 0 && winner == 0) {
        isFilled = isBoardFull(); // controls empty cells

        if(isFilled == 0 && userSequence != "user2")
            do {
            	cout << "Living Cell: " << ConnectFour::livingCell << endl;
                isSaved = 0;
                cout << "user1's move: ";
                input = takeInput(); // getting move from user1
                if (input.length() == 1) {
                    column = input[0] - 'a';
                    user1 = play(column); // makes move

                } else if (input.substr(0, 4) == "save" ||
                           input.substr(0, 4) == "SAVE") {
                    saveGame("user1", input.substr(4));
                    isSaved = 1;
                }
                else if(input.substr(0, 4) == "load" ||
                        input.substr(0, 4) == "LOAD") {
                    loadGame(input.substr(4));
                    return 1;

                }
                if(user1 == 0 && isFilled == 0 && isSaved == 0)
                    cerr << "Invalid move, please try again" << endl;

                isFilled = isBoardFull();
            } while ((user1 == 0 && isFilled == 0) || isSaved == 1);

        playerTurn++;
        ConnectFour::livingCellCounter();
        winner = checkWinner('X'); // checks winner for user1
        printBoard();
        if(winner == 1)
            cout << "Winner is user1.\n";

        // if user1 is not winner, user2 makes move
        if(winner == 0) {
            if(userSequence == "user2")
                userSequence = "none";
            isFilled = isBoardFull();
            if(isFilled == 0)
                do {
                    isSaved = 0;
                    cout << "user2's move: ";
                    input = takeInput(); // getting move from user1
                    if(input.length() == 1) {
                        column = input[0] - 'a';
                        user2 = play(column);// makes move
                    }
                    else if(input.substr(0, 4) == "save" ||
                            input.substr(0, 4) == "SAVE") {

                        saveGame("user2", input.substr(4));
                        isSaved = 1;
                    }

                    else if(input.substr(0, 4) == "load" ||
                            input.substr(0, 4) == "LOAD") {

                        loadGame(input.substr(4));
                        return 1;
                    }

                    if(user2 == 0 && isFilled == 0 && isSaved == 0)
                        cerr << "Invalid move, please try again" << endl;

                    isFilled = isBoardFull();
                } while ((user2 == 0 && isFilled == 0) || isSaved == 1);
            playerTurn++;
            ConnectFour::livingCellCounter();
            winner = checkWinner('O');
            printBoard();

            if(winner == 2)
                cout << "Winner is user2.\n";
        }
    }
    // If there is no winner and board is filled, it is executed
    if(winner == 0 && isFilled == 1)
        cout << "Nobody won the game.\n";
    return 0;
}

int ConnectFour::play(int column) {
    int row = height - 1;
    // If desired row is filled by users or computer, row is reduced.
    //>>>>>>Row always initializes to row = size-1 in gameplay function.<<<<<
    while(row >= 0 && (gameCells[row][column].getCellValue() == 'O' ||
           gameCells[row][column].getCellValue() == 'X')) 
        row--;

    // If there is no row for move return 0
    if(row == -1)
        return 0; // It means invalid move
    else { // // If move is valid, symbol('O' or 'X') is written.
        if(playerTurn % 2 == 0)
            gameCells[row][column].setCell('X');
        else if(playerTurn % 2 == 1)
            gameCells[row][column].setCell('O');
        return 1; // It means valid move
    }
}

bool ConnectFour::compareGame(ConnectFour otherGame) {
    // They keep number of 'X' characters. Condition is
    // end of x secuence must have empty cell, so 
    // user can make move.
    // Acoording to the character number returns good game.
    int hor[2] = {};
    int ver[2] = {};
    int hor2[2] = {};
    int ver2[2] = {};

    int firstGame; 
    int secondGame;

	// checks vertical and horizontal dimensions
    verticalMoveControl(ver, 'X');
    horizontalMoveControl(hor, 'X');

    otherGame.verticalMoveControl(ver2, 'X');
    otherGame.horizontalMoveControl(hor2, 'X');

    if(ver[1] > hor[1])
        firstGame = ver[1];
    else 
        firstGame = hor[1];

    if(ver2[1] > hor2[1])
        secondGame = ver2[1];
    else 
        secondGame = hor2[1];

    if(firstGame > secondGame)
        return true;
    else
        return false;
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
    if(ver[1] > hor[1])
        result = ver[0];
    else
        result = hor[0];

    // If winning or losing is close, makes that moves
    if(ver[1] == 3)
        result = ver[0];
    else if(hor[1] == 3)
        result = hor[0];
    else if(preventHor[1] == 3)
        result = preventHor[0];
    else if(preventVer[1] == 3)
        result = preventVer[0];

    // there is no logical move then it finds first empty cell
    if(result == 0)
        for(int i = 0; i < height && found == 0; i++)
            for(int j = 0; j < width && found == 0; j++)
                if(gameCells[i][j].getCellValue() == '.') {
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
    while(row >= 0 && (gameCells[row][column].getCellValue() == 'O' ||
           gameCells[row][column].getCellValue() == 'X')) 
        row--;

    // If there is no row for move return 0
    if(row == -1)
        return 0; // It means invalid move
    else { // // If move is valid, symbol('O' or 'X') is written.
        gameCells[row][column].setCell('O');
        return 1; // It means valid move
    }
}

void ConnectFour::verticalMoveControl(int result[2], char symbol) {
    int counter = 0; // keeps number of symbols over and over
    int max = 0;     // max number of symbols
    int i, j;
    int lastIndex;

    // bottom to up
    for(j = 0; j < width; j++) {
        for(i = height - 1; i >= 0; i--) {
            // counts number of symbols
            if (gameCells[i][j].getCellValue() == symbol)
                counter++;
            // If there isnt computer symbol, starts counting again
            else if(gameCells[i][j].getCellValue() != symbol) {
                lastIndex = i;
                // If maximum number is found and there is a empty cell,
                // place is assigned to result
                if(counter > max &&
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
    for(k = height - 1; k >= 0; k--) {
        for (i = 0; i <= width - 4; i++) {
            for (j = i, a = 0; a < 4; j++, a++)
                temp[a] = gameCells[k][j].getCellValue();//four cells from board

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

ConnectFour::ConnectFour() {
    width = 4;
    height = 4;
    userSequence = "user1";
    gameMode = 'P';

    for(int i = 0; i < 4; i++)
        gameCells.push_back(vector<Cell>());

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            gameCells[i].push_back(Cell('.', i, j));
}

ConnectFour::ConnectFour(int heightValue, int widthValue)
        : width(widthValue), height(heightValue)
{
    for(unsigned int i = 0; i < height; i++)
        gameCells.push_back(vector<Cell>());

    for(unsigned int i = 0; i < height; i++)
        for(unsigned int j = 0; j < width; j++)
            gameCells[i].push_back(Cell('.', i, j));
}

void ConnectFour::resizeTheBoard(int heightValue, int widthValue)
{
    width = widthValue;
    height = heightValue;

    gameCells.resize(height);
    for(int i = 0; i < height; ++i)
        gameCells[i].resize(width);

    for(int i = 0; i < height; ++i)
        for(int j = 0; j < width; ++j)
            gameCells[i][j].setCell('.');
}

int ConnectFour::checkWinner(char symbol)
{
    int result = 0;
    int i, j;
    char lowerCase =  symbol + ('a' - 'A'); // converts letter to lowercase

    // It controls every cell in the board for finding four same symbols
    for( i = 0; i < height && result == 0; i++)
        for( j = 0; j < width && result == 0; j++) {
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
    if(result == 1 && symbol == 'O') 
        //it indicates for pvp user2 is winner, for pve winner is computer
        return 2;

    return result;
}

int ConnectFour::isBoardFull() const
{
	int result = 1;
	// It scans every cell in the board
    for(int i = 0; i < height && result == 1; i++)
        for(int j = 0; j < width && result == 1; j++)
            if(gameCells[i][j].getCellValue() == '.')
                result = 0;

    // If there is an empty cell returns 0, otherwise returns 1
    return result;
}

string ConnectFour::takeInput() {
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
            if( letter > ( width - 1 + 'a') || letter < 'a' ) {
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

void ConnectFour::saveGame(const string userSequence, const string fileName) {
    ofstream outStream;
    int currentCell = 0;

    outStream.open(fileName.c_str()); // opening or creating file
    if(outStream.fail()) { // if there is an error, prints error
        cerr << "Output file openning failed." << endl;
        exit(1);
    }

    // count livingCell
    for(int j = 0; j < height; j++)
        for(int i = 0; i < width; i++) {
            if(gameCells[j][i].getCellValue() != '.')
                currentCell++;
        }

	// writes data to file
    outStream << currentCell << endl 
    		  << height <<  " " << width << endl  
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

void ConnectFour::loadGame(const string fileName) {
    ifstream inStream;
    char temp;
    int cellNumber;
    int totalCell = ConnectFour::livingCell;
    int currentCell = 0;

    inStream.open(fileName.c_str()); // opening file
    if(inStream.fail()) {
        cerr << "Input file opening failed." << endl;
        exit(1);
    }

    // count livingCell
    for(int j = 0; j < height; j++)
        for(int i = 0; i < width; i++) {
            if(gameCells[j][i].getCellValue() != '.')
                currentCell++;
        }


	// takes data from file
    inStream >> cellNumber >> height >> width >> userSequence >> gameMode;

    // set living cell number
    totalCell += cellNumber;
    totalCell -= currentCell;
    ConnectFour::setLivingCell(totalCell);

    // resize new board
    resizeTheBoard(height, width);

	// reads all board cell
    for(int j = 0; j < height; j++)
        for(int i = 0; i < width; i++) {
            inStream >> temp;
            gameCells[j][i] = Cell(temp, j, i);
        }

    inStream.close();
}

void ConnectFour::Cell::printCellValues() {
	cout << "Row Number: " << rowNumber;
	cout << endl << "Position: " << position;
	cout << endl << "cellValue: " << cellValue << endl;
}

ConnectFour::Cell::Cell(char ch, int row, int column) {
    cellValue = ch;
    rowNumber = row + 1;
    position = 'A' + column;
}

ConnectFour::Cell::Cell() { }

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
        if(cin.fail()) {
            cin.clear();
            cin.ignore();
            isInt = 0;
        }
     // If the size of the board isnt between 4 and 20, it takes another input
        if(width <= 0 || isInt == 0)
            cerr << "Invalid board size, enter a diffirent value: ";
    } while(width <= 0 || isInt == 0);

    cout << "Enter height: ";
    do {
    	isInt = 1;
        cin >> height;
        if(cin.fail()) {
            cin.clear();
            cin.ignore();
        	isInt = 0;
        }
      // If the size of the board isnt between 4 and 20, it takes another input
        if(height <= 0 || isInt == 0)
            cerr << "Invalid board size, enter a diffirent value: ";
    } while(height <= 0 || isInt == 0);
}
