/*!Begin Snippet:file*/
import java.util.*;

/**
 * This class implements a method that obtains an XML
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
public class XMLBorrowersFormatter
	implements BorrowersFormatter  {

	/* Line separator */
	private final static String NEW_LINE = System.getProperty("line.separator");

	/* single instance of this class */
	static private XMLBorrowersFormatter singletonInstance = null;

	/**
	 * Obtains the single instance of class
	 * <code>XMLBorrowersFormatter</code>
	 *
	 * @return the single instance  of class
	 *         <code>XMLBorrowersFormatter</code>
	 */
	static public XMLBorrowersFormatter getSingletonInstance() {

		if (singletonInstance == null) {
			singletonInstance = new XMLBorrowersFormatter();
		}

		return singletonInstance;
	}

	/*
	 * The constructor is declared private so other classes cannot
	 * create an instance of this class.
	 */
	private XMLBorrowersFormatter() {

	}

	/**
	 * Obtains an XML representation of the specified borrower
	 * database.
	 *
	 * @param borrowerDB  the borrower database.
	 * @return  a XML representation of the specified
	 *          {@link BorrowerDatabase} object.
	 */
	public String formatBorrowers (BorrowerDatabase borrowerDB) {

		String out = "<BorrowerDatabase>" + NEW_LINE ;

		for (Borrower borrower : borrowerDB) {
			out += "  <Borrower id=\""
					+ borrower.getId()
					+ "\" name=\""
					+ borrower.getName()
					+ "\">"
					+ NEW_LINE;

			BorrowedItems items = borrower.getBorrowedItems();

			if (items.getNumberOfItems() > 0) {
				out += "    <BorrowedItems>" + NEW_LINE;

				for (CatalogItem item : items) {
					out += "      <CatalogItem id=\""
							+ item.getCode()
							+ "\">"
							+ item.getTitle()
							+ "</CatalogItem>" + NEW_LINE;
				}
				out += "    </BorrowedItems>" + NEW_LINE;
			}
			out += "  </Borrower>" + NEW_LINE;
		}
		out += "</BorrowerDatabase>";

		return out;
	}
}
/*!End Snippet:file*/