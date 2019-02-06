
public class GTUSetException extends Exception {
	public String message;
	public GTUSetException() {}
	public GTUSetException(String theMessage) {
		message = theMessage;
	}
	public String getMessage() { return message; }
}
