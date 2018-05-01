package pkg141044071.hw8;
/*
    Author: Islam Goktan SELCUK
    Number: 141044071

 */
import java.awt.FlowLayout;
import java.awt.Point;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;


public class ConnectFour extends JFrame {

    protected int length; // oyun tahtasinin bir kenarinin boyutu
    protected String gameMode; // oyun modu pvp / pve
    protected int getLength() { return length; }
    protected Icon whiteCell; // bos olan hucreye ait icon
    protected Icon redCell; // kirmizi hucreye ait icon
    protected Icon yellowCell;
    protected int playerTurn; // kullanici sirasini belirtir
    protected ButtonHandler handler;
    protected Cell gameBoard[][]; // oyun tahtasi

    protected class Cell {
        Cell() {
            // cell gecerli buttonun rengine gore olusturulur.
                cellColour = whiteCell;
                button = new JButton(whiteCell);
        }

        Cell(final Icon theCellColour, final int row, final int column) {
            // cell buton rengi , gecerli satır ve konuma gore olusturulur.
                cellColour = theCellColour;
                rowNumber = row + 1;
                position = (char)(column + 'A');
                button = new JButton(whiteCell);
        }

        // cell'in rengini return eder.
        void setColour(final Icon theCellColour) {
                cellColour = theCellColour;
                button.setIcon(theCellColour);
        }

        void setRowNumber(final int row) {
                rowNumber = row;
        }

        void setPosition(final char column) {
                position = column;
        }

        JButton getButton() { return button; }
        Icon getColour() { return cellColour; }
        int getRowNumber() { return rowNumber; }
        char getPosition() { return position; }

        // gecerli cell icin olusturulan buton objesi
        private JButton button; 
        // objenin kime ait oldugunu be oyun sirasinda yapilan hamleye gore
        // cellin rengini belirtir.
        private Icon cellColour;
        // cellin bulundugu satir
        private int rowNumber;
        // bulundugu sutun
        private char position;
    }

    public ConnectFour() throws ConnectFourException
    {
            // layout olusturulur.
            super("ConnectFour");
            setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));	

            String input = 
                JOptionPane.showInputDialog("Enter length of board: ");

            playerTurn = 0;

            // Kullanicidan oyun modu alinir.
            gameMode = 
                JOptionPane.showInputDialog("Enter gamemod('p' for pvp and 'c' for pve): ");

            // gecersiz input icin exception firlatilir.
            if(gameMode.equalsIgnoreCase("c") == false &&
                    gameMode.equalsIgnoreCase("p") == false)
                    throw new ConnectFourException("Invalid game mode!");

            length = Integer.parseInt(input);
            if(length < 4 || length > 10)
                    throw new ConnectFourException("Length has invalid value!");

            // cell objeleri icin icon degiskenleri olusturulur.
            handler = new ButtonHandler();
            whiteCell = new ImageIcon( getClass().getResource("boardCell.png"));
            redCell = new ImageIcon(getClass().getResource("redCell.png"));
            yellowCell = new ImageIcon(getClass().getResource("yellowCell.png"));

            gameBoard = new Cell[length][length];
            for(int i = 0; i < length; i++) {
                for(int j = 0; j < length; j++) {
                    // handler icin bir index string i olusturulur. Boylece
                    // handler gecerli hucreyi taniyabilir.
                    String index = "" + i + j;
                    // cell objesi olusturulur.
                    gameBoard[i][j] = new Cell(whiteCell, i, j);
                    // handler icin butona command gonderilir.
                    gameBoard[i][j].getButton().setActionCommand(index);
                    // butonlarin aralarindaki bosluk silinir.
                    gameBoard[i][j].getButton().setBorder(null);
                    // butonlar layout'a eklenir.
                    add(gameBoard[i][j].getButton());
                    // her butona actionListener eklenir.
                    gameBoard[i][j].getButton().addActionListener(handler);

                }
            }		

    }

    public void clearBoard() throws ConnectFourException {
            //Yeniden olusturulmak üzere tum butonlar silinir.
            for(int i = 0; i < length; i++)
                for(int j = 0; j < length; j++)
                    remove(gameBoard[i][j].getButton());

            // yeni input degerleri alinir.
            String input = 
                JOptionPane.showInputDialog("Enter length of board: ");
            gameMode = 
                JOptionPane.showInputDialog("Enter gamemod('p' for pvp and 'c' for pve): ");

            //Gecersiz inputlar icin exception firlatilir.
            if(gameMode.equalsIgnoreCase("c") == false && 
                    gameMode.equalsIgnoreCase("p") == false)
                throw new ConnectFourException("Invalid game mode!");

            length = Integer.parseInt(input);
            if(length < 4 || length > 10)
                throw new ConnectFourException("Length has invalid value!");

            playerTurn = 0;

            gameBoard = new Cell[length][length];

            int left = 1;
            int bottom = 85;
            for(int i = 0; i < length; i++) {
                for(int j = 0; j < length; j++) {
                    String index = "" + i + j;
                    gameBoard[i][j] = new Cell(whiteCell, i, j);
                    gameBoard[i][j].getButton().setActionCommand(index);
                    gameBoard[i][j].getButton().setBorder(null);
                    add(gameBoard[i][j].getButton());
                    gameBoard[i][j].getButton().addActionListener(handler);
                }
            }	

            setSize( 85 * length, 92 * length );
    }


    public class GamePlay {

        public int play(int column) {
            //Row always initializes to row = size-1 in gameplay function.
            int row = length - 1;
            // If desired row is filled by users or computer, row is reduced.
            while( row >= 0 && 
                   (gameBoard[row][column].getColour() == yellowCell
                   || gameBoard[row][column].getColour() == redCell) )
                    row--;
    // If there is no row for move return 0
            if(row == -1)
                    return 0;// It means invalid move
            else {
                    if(playerTurn % 2 == 0)
                            gameBoard[row][column].setColour(redCell);
                    else if(playerTurn % 2 == 1)
                            gameBoard[row][column].setColour(yellowCell);
                    return 1;
            }
        }

            public int checkWinner(Icon cellColour) {
                int result = 0;
                int i, j;
    // It controls every cell in the board for finding four same symbols
                for( i = 0; i < length && result == 0; i++)
                    for( j = 0; j < length && result == 0; j++) {
                        // controls from bottom to up
                        if (i >= 3 &&
                            gameBoard[i][j].getColour() == cellColour &&
                            gameBoard[i - 1][j].getColour() == cellColour &&
                            gameBoard[i - 2][j].getColour() == cellColour &&
                            gameBoard[i - 3][j].getColour() == cellColour) {
                            result = 1;
                        }
                            // controls from left to right
                        else if (j <= length - 4 &&
                            gameBoard[i][j].getColour() == cellColour &&
                            gameBoard[i][j + 1].getColour() == cellColour &&
                            gameBoard[i][j + 2].getColour() == cellColour &&
                            gameBoard[i][j + 3].getColour() == cellColour) {
                            result = 1;
                        }
                            // controls left diagonal
                        else if (i >= 3 && j >= 3 &&
                            gameBoard[i][j].getColour() == cellColour &&
                            gameBoard[i - 1][j - 1].getColour() == cellColour &&
                            gameBoard[i - 2][j - 2].getColour() == cellColour &&
                            gameBoard[i - 3][j - 3].getColour() == cellColour) {

                            result = 1;
                        }
                            // controls right diagonal
                        else if (i >= 3 && j <= length - 4 &&
                            gameBoard[i][j].getColour() == cellColour &&
                            gameBoard[i - 1][j + 1].getColour() == cellColour &&
                            gameBoard[i - 2][j + 2].getColour() == cellColour &&
                            gameBoard[i - 3][j + 3].getColour() == cellColour) {

                            result = 1;
                        }
                    }


                // because the winner is determined by this data
                if(result == 1 && cellColour == yellowCell) {
                    //it indicates for pvp user2 is winner, for pve winner is computer
                    JOptionPane.showMessageDialog(ConnectFour.this, String.format("Player 2 is win!"));
                    return 2;
                }
                if(result == 1)
                    JOptionPane.showMessageDialog(ConnectFour.this, String.format("Player 1 is win!"));
                return result;
            }

            public int play() {
                // data for winning moves
                int hor[] = new int[2];        // takes result from functions
                int ver[] = new int[2];
                // data for prevention moves
                int preventHor[] = new int[2];
                int preventVer[] = new int[2];

                int row;
                int column;
                int result = 0; // target place for move
                int found = 0;

                // prevention moves for user
                verticalMoveControl(preventVer, redCell);
                horizontalMoveControl(preventHor, redCell);

                // winning moves
                verticalMoveControl(ver, yellowCell);
                horizontalMoveControl(hor, yellowCell);

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
                    for(int i = 0; i < length && found == 0; i++)
                        for(int j = 0; j < length && found == 0; j++)
                            if(gameBoard[i][j].getColour() == whiteCell) {
                                result = j;
                                found = 1;
                            }

                column = result; // target place
                row = length - 1;


                // If desired row is filled by users or computer, row is reduced.
                //Row always initializes to row = size-1 in gameplay function.
                while(row >= 0 && 
                        (gameBoard[row][column].getColour() == redCell ||
                            gameBoard[row][column].getColour() == yellowCell)) 
                    row--;

                // If there is no row for move return 0
                if(row == -1)
                    return 0; // It means invalid move
                else { // // If move is valid, symbol('O' or 'X') is written.
                    gameBoard[row][column].setColour(yellowCell);
                    return 1; // It means valid move
                }
            }

            void verticalMoveControl(int result[], Icon cellColour) {
                int counter = 0; // keeps number of symbols over and over
                int max = 0;     // max number of symbols
                int i, j;
                int lastIndex;

                // bottom to up
                for(j = 0; j < length; j++) {
                    for(i = length - 1; i >= 0; i--) {
                        // counts number of symbols
                        if (gameBoard[i][j].getColour() == cellColour)
                            counter++;
                        // If there isnt computer symbol, starts counting again
                        else if(gameBoard[i][j].getColour() != cellColour) {
                            lastIndex = i;
                            // If maximum number is found and there is a empty cell,
                            // place is assigned to result
                            if(counter > max &&
                                    gameBoard[lastIndex][j].getColour() == whiteCell) {
                                max = counter;
                                result[0] = j;
                            }
                            counter = 0;
                        }
                    }
                }
                result[1] = max; // maximum number of symbols
            }

            void horizontalMoveControl(int result[], Icon cellColour) {
                int counter = 0;
                int max = 0;
                int i, j, a, k; // counters
                Icon temp[] = new Icon[4]; // It keeps every side by side 4 cells in the board

                result[0] = 0;
                // left to right
                for(k = length - 1; k >= 0; k--) {
                    for (i = 0; i <= length - 4; i++) {
                        for (j = i, a = 0; a < 4; j++, a++)
                            temp[a] = gameBoard[k][j].getColour();//four cells from board

                        counter = 0;
                        for (a = 0; a < 4 && counter != -1; a++) {
                            if (temp[a] == cellColour) // counting symbols
                                counter++;
                            // If there is a opponent symbol, stops counting
                            else if ( (cellColour == redCell && 
                                    temp[a] == yellowCell) ||
                            (cellColour == yellowCell && temp[a] == redCell) )
                                counter = -1;
                        }
                        if (counter > max) {
                            for(int b = 0, y1 = j - 4; b < 4; b++, y1++)
                            // If there is a empty cell and down of the cell is filled,
                            // assigns place for move
                                if (k + 1 == length ||
                                    gameBoard[k + 1][y1].getColour() != whiteCell)
                                    if (gameBoard[k][y1].getColour() == whiteCell) {
                                        result[0] = y1;
                                        max = counter;
                                    }
                        }
                    }
                }

                result[1] = max;
            }

    }


    private class ButtonHandler implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent event) {
            // button icin olusturulan komut alinir.(Buttonun ait oldugu
            // cellin indexi gonderilir.
            String index = event.getActionCommand();
            // alinan index integer a donusturulur.
            int intIndex = Integer.parseInt(index);
            // column degeri hesaplanir.
            int y = intIndex % 10; 
            // oyunun oynanmasi icin gamePlay sınıfından obje olusturulur.
            GamePlay a = new GamePlay();
            // pvp modu icin calisir
            if(gameMode.equalsIgnoreCase("p")) {
                //kullanici hamle yaptikdan sonra playerTurn artirlir.
                    a.play(y);
                    playerTurn++;
            }
            // player versus computer icin calisir
            if(gameMode.equalsIgnoreCase("c")) {
                // once kullanici icin play fonku cagirilir, sonra computer icin
                    a.play(y);
                    a.play();
            }

            if(a.checkWinner(redCell) > 0 || 
                    a.checkWinner(yellowCell) > 0) {
                    // Burada try/catch kullandim. Cunku actionPerformed fonksiyonunun 
                    // ismine kendi exception sinifim eklenemiyor. 
                    try {
                            clearBoard();
                    } catch (ConnectFourException e) {
                            System.out.println(e);
                    }
            }
        }
    }
	
}
