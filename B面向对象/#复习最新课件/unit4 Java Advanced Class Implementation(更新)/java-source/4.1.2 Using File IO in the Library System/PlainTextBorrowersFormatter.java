/*!Begin Snippet:file*/
import java.util.*;

/**
 * This class implements a method that obtains a plain text
 * representation of a {@link BorrowerDatabase} object.
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see BorrowersFormatter
 * @see BorrowerDatabase
 * @see Borrower
 * @see BorrowedItems
 * @see CatalogItem
 */
public class PlainTextBorrowersFormatter
	implements BorrowersFormatter  {

	/* Line separator */
	private final static String NEW_LINE = System.getProperty("line.separator");

	/* single instance of this class */
	static private PlainTextBorrowersFormatter singletonInstance = null;

	/**
	 * Obtains the single instance of class
	 * <code>PlainTextBorrowersFormatter</code>
	 *
	 * @return the single instance  of class
	 *         <code>PlainTextBorrowersFormatter</code>
	 */
	static public PlainTextBorrowersFormatter getSingletonInstance(){

		if (singletonInstance == null) {
			singletonInstance = new PlainTextBorrowersFormatter();
		}

		return singletonInstance;
	}

	/*
	 * The constructor is declared private so other classes cannot
	 * create an instance of this class.
	 */
	private PlainTextBorrowersFormatter() {

	}

	/**
	 * Obtains a plain text representation of the specified borrower
	 * database.
	 *
	 * @param borrowerDB  the borrower database.
	 * @return  a plain text representation of the specified
	 *          {@link BorrowerDatabase} object.
	 */
	public String formatBorrowers (BorrowerDatabase borrowerDB) {

		String out = "Borrower Database" + NEW_LINE;

		for (Borrower borrower : borrowerDB) {

			out += borrower.getId() + "_" + borrower.getName();

			for (CatalogItem item : borrower.getBorrowedItems()) {

				out += "_" + item.getCode();
			}
			out += NEW_LINE;
		}

		return out;
	}
}
/*!End Snippet:file*/