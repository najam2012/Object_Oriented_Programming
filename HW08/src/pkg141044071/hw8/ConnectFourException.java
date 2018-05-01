package pkg141044071.hw8;
/*
    Author: Islam Goktan SELCUK
    Number: 141044071

 */


public class ConnectFourException extends Exception {
    private String message;

    public ConnectFourException() {
		message = "There is an exception!";
	}
	

    public ConnectFourException(String theMessage) {
		message = theMessage;
	}
	
	@Override
	public String toString() {
		return String.format("%s", message);
	}

}
