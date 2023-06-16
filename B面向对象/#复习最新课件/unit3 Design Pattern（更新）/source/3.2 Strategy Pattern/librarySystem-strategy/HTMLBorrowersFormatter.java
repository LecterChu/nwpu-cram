/*!Begin Snippet:file*/
import java.util.*;

/**
 * This class implements a method that obtains an HTML
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
public class HTMLBorrowersFormatter
	implements BorrowersFormatter  {

	/* Line separator */
	private final static String NEW_LINE = System.getProperty("line.separator");

	/* single instance of this class */
	static private HTMLBorrowersFormatter singletonInstance = null;

	/**
	 * Obtains the single instance of class
	 * <code>HTMLBorrowersFormatter</code>
	 *
	 * @return the single instance  of class
	 *         <code>HTMLBorrowersFormatter</code>
	 */
	static public HTMLBorrowersFormatter getSingletonInstance() {

		if (singletonInstance == null) {
			singletonInstance = new HTMLBorrowersFormatter();
		}

		return singletonInstance;
	}

	/*
	 * The constructor is declared private so other classes cannot
	 * create an instance of this class.
	 */
	private HTMLBorrowersFormatter() {

	}

	/**
	 * Obtains an HTML representation of the specified borrower
	 * database.
	 *
	 * @param borrowerDB  the borrower database.
	 * @return  an HTML representation of the specified
	 *          {@link BorrowerDatabase} object.
	 */
	public String formatBorrowers (BorrowerDatabase borrowerDB) {

		String out = "<html>"
				+ NEW_LINE
				+ "  <body>"
				+ NEW_LINE + ""
				+ "    <center><h2>Borrower Database</h2></center>"
				+ NEW_LINE;

		for (Borrower borrower : borrowerDB) {
			out += "    <hr>"
					+ NEW_LINE
					+ "    <h4>"
					+ borrower.getId()
					+ " "
					+ borrower.getName()
					+ "</h4>"
					+ NEW_LINE;

			BorrowedItems items = borrower.getBorrowedItems();

			if (items.getNumberOfItems() > 0) {
				out += "      <blockquote>" + NEW_LINE;

				for (CatalogItem item : items) {
					out += "         "
							+ item.getCode()
							+ " "
							+ item.getTitle()
							+ "<br>"
							+ NEW_LINE;
				}
				out += "      </blockquote>" + NEW_LINE;
			}
		}
		out += "  </body>" + NEW_LINE + "</html>";

		return out;
	}
}
/*!End Snippet:file*/