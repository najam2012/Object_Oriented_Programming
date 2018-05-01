/*
    Author: Islam Goktan SELCUK
    Number: 141044071

 */
package pkg141044071.hw8;

import javax.swing.JFrame;


public class Hw8 {

    public static void main(String[] args) throws ConnectFourException {

        try {
            ConnectFour game = new ConnectFour(); // create ButtonFrame
            game.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
            // Oyun baslarken alinan boyuta gore oyun tahtasi olusturulur
            int length = game.getLength();
            game.setSize( 85 * length, 92 * length ); // set frame size
            game.setVisible( true ); // display frame
        }
        catch(ConnectFourException e) {
            System.out.println(e);
        }
    }
    
}
