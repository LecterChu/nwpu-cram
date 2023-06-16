/*!Begin Snippet:file*/
/**
 * This interface defines a method that obtains a string
 * representation of a {@link BorrowerDatabase} object.
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see BorrowerDatabase
 */
public interface BorrowersFormatter  {

	/**
	 * Obtains the string representation of the specified borrower
	 * database.
	 *
	 * @param borrowerDB  the borrower database.
	 * @return  the string representation of the specified
	 *          {@link BorrowerDatabase} object.
	 */
	String formatBorrowers (BorrowerDatabase borrowerDB);
}
/*!End Snippet:file*/