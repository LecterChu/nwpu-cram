
public class EmptyException extends Exception{
	 /**
     * Constructs a new instance of <code>OutOfRangeException</code>.
     */
    public EmptyException() {

    }

    /**
     * Constructs a new instance of <code>OutOfRangeException</code>
     * that includes an explanation.
     *
     * @param message  Additional information about this exception.
     *                     Can be null.
     */
    public EmptyException(String message) {

        super(message);
    }

}
