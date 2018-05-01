
public class GTUSetException extends Exception {
	public String massage;
	public GTUSetException() {}
	public GTUSetException(String theMassage) {
		massage = theMassage;
	}
	public String getMessage() { return massage; }
}
