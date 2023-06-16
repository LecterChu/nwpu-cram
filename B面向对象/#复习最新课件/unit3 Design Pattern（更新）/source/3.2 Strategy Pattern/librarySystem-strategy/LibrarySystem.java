/*!Begin Snippet:file*/
import java.io.*;
import java.util.*;

/**
 * This class implements a library system.
 *
 * @author iCarnegie
 * @version 1.1.0
 * @see CatalogItem
 * @see Book
 * @see Recording
 * @see Catalog
 * @see Borrower
 * @see BorrowerDatabase
 * @see BorrowersFormatter
 * @see PlainTextBorrowersFormatter
 * @see HTMLBorrowersFormatter
 * @see XMLBorrowersFormatter
 */
public class LibrarySystem  {

	private static BufferedReader  stdIn =
		new  BufferedReader(new  InputStreamReader(System.in));
	private static PrintWriter  stdOut =
		new  PrintWriter(System.out, true);
	private static PrintWriter  stdErr =
		new  PrintWriter(System.err, true);

	private BorrowerDatabase borrowerDB;

	private BorrowersFormatter borrowersFormatter;

	/**
	 * Loads a library catalog and borrower database and then
	 * starts the application.
	 *
	 * @param args  String arguments.  Not used.
	 * @throws IOException if there are errors in the input.
	 */
	public static void  main(String[]  args) throws IOException {

		LibrarySystem  app = new  LibrarySystem();

		app.run();
	}

	/**
	 * Creates a <code>LibrarySystem</code> object.
	 */
	private LibrarySystem() {

		borrowerDB = loadBorrowers(loadCatalog());
		borrowersFormatter =
			PlainTextBorrowersFormatter.getSingletonInstance();
	}

	/**
	 * Loads catalog data.
	 */
	private Catalog loadCatalog() {

		Catalog catalog = new Catalog();

		catalog.addItem(new Book("B001",
			"Effective Java Programming", 2001,
			"Joshua Bloch", 252));
		catalog.addItem(new Book("B002",
			"Design Patterns", 1995,
			"Erich Gamma et al", 395));
		catalog.addItem(new Book("B003",
			"Refactoring", 1999,
			"Martin Fowler", 431));
		catalog.addItem(new Book("B004",
			"The Mythical Man-Month", 1995,
			"Frederick P. Brooks", 322));
		catalog.addItem(new Book("B005",
			"Code Complete", 1993,
			"Steve C McConnell", 857));
		catalog.addItem(new Book("B006",
			"The Psychology of Comp. Progr.", 1998,
			"Gerald M. Weinberg", 360));
		catalog.addItem(new Book("B007",
			"Programming Pearls ", 1999,
			"Jon Bentley", 239));
		catalog.addItem(new Book("B008",
			"The Practice of Programming", 1999,
			"Brian W. Kernighan", 257));
		catalog.addItem(new Book("B009",
			"Peopleware", 1999,
			"Tom Demarco", 245));
		catalog.addItem(new Book("B010",
			"The Java Programming Language", 2000,
			"Ken Arnold", 595));
		catalog.addItem(new Book("B011",
			"Core J2EE Patterns", 2001,
			"Deepak Alur", 496));
		catalog.addItem(new Book("B012",
			"Rapid Development", 1996,
			"Steve C McConnell", 680));
		catalog.addItem(new Book("B013",
			"Applying UML and Patterns", 2001,
			"Craig Larman", 656));
		catalog.addItem(new Book("B014",
			"The Little Schemer", 1995,
			"Daniel P. Friedman", 216));
		catalog.addItem(new Book("B015",
			"Agile Software Development", 2001,
			"Alistair Cockburn", 256));
		catalog.addItem(new Recording("R001",
			"Getz/Gilberto", 1963,
			"Stan Getz and João Gilberto", "CD"));
		catalog.addItem(new Recording("R002",
			"Kind of Blue", 1997,
			"Miles Davis", "CD"));
		catalog.addItem(new Recording("R003",
			"Supernatural", 1999, "Santana",
			"Tape"));
		catalog.addItem(new Recording("R004",
			"Private Collection", 1983,
			"Jon & Vangelis", "Tape"));
		catalog.addItem(new Recording("R005",
			"Abbey Road", 1969,
			"Beatles", "CD"));
		catalog.addItem(new Recording("R006",
			"Joshua Tree", 1990,
			"U2", "CD"));

		return catalog;
	}

	/**
	 * Loads a borrower database.
	 */
	private BorrowerDatabase loadBorrowers(Catalog catalog) {

		BorrowerDatabase borrowerDB = new BorrowerDatabase();

		Borrower borrower = new Borrower("ID001", "James Addy");

		borrower.getBorrowedItems().addItem(
			catalog.getItem("B003"));
		borrower.getBorrowedItems().addItem(
			catalog.getItem("R001"));
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B012"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID002", "John Doust");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID003", "Constance Foster");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B006"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID004", "Harold Gurske");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B002"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID005", "Mary A. Rogers");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID006", "Laura Novelle");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B007"));
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B009"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID007", "David M. Prescott");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B011"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID008", "Francis Matthews");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("R003"));
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B005"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID009", "Thomas Ferris");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID010", "John Johnson");
		borrower.getBorrowedItems().addItem(
			catalog.getItem("B004"));
		borrowerDB.addBorrower(borrower);

		return borrowerDB;
	}

	/**
	 * Presents the user with a menu of options and executes the
	 * selected task.
	 */
	private void run() throws IOException  {

		int  choice = getChoice();

		while (choice != 0)  {

			if (choice == 1)  {
				setBorrowersFormatter(
					PlainTextBorrowersFormatter.getSingletonInstance());
			} else if (choice == 2)  {
				setBorrowersFormatter(
					HTMLBorrowersFormatter.getSingletonInstance());
			} else if (choice == 3)  {
				setBorrowersFormatter(
					XMLBorrowersFormatter.getSingletonInstance());
			}
			displayBorrowers();

			choice = getChoice();
		}
	}

	/**
	 * Displays a menu of options and verifies the user's choice.
	 *
	 * @return an integer in the range [0,3]
	 */
	private int  getChoice() throws IOException  {

		int  input;

		do  {
			try  {
				stdErr.println();
				stdErr.print("[0]  Quit\n"
				             + "[1]  Display Plain Text\n"
				             + "[2]  Display HTML\n"
				             + "[3]  Display XML\n"
				             + "choice> ");
				stdErr.flush();

				input = Integer.parseInt(stdIn.readLine());

				stdErr.println();

				if (0 <= input && 3 >= input)  {
					break;
				} else {
					stdErr.println("Invalid choice:  " + input);
				}
			} catch (NumberFormatException  nfe)  {
				stdErr.println(nfe);
			}
		}  while (true);

		return  input;
	}

	/**
	 * Changes the format in which the borrower database will be
	 * displayed.
	 *
	 * @param newFormatter format in which the borrower database will
	 *                     be displayed.
	 */
	private void setBorrowersFormatter(
		BorrowersFormatter newFormatter){

		borrowersFormatter = newFormatter;
	}

	/**
	 * Displays the borrowers in the current format.
	 */
	private void displayBorrowers() {

		stdOut.println(
			borrowersFormatter.formatBorrowers(borrowerDB));
	}
}
/*!End Snippet:file*/
