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
 * @see BorrowedItems
 * @see BorrowerDatabase
 */
public class LibrarySystem  {

	private static BufferedReader  stdIn =
		new  BufferedReader(new  InputStreamReader(System.in));
	private static PrintWriter  stdOut = new  PrintWriter(System.out, true);
	private static PrintWriter  stdErr = new  PrintWriter(System.err, true);

	private Catalog  catalog;
	private BorrowerDatabase borrowerDB;

	/**
	 * Loads the information of the library catalog and
	 * borrowers database and starts the application.
	 *
	 * @param args  String arguments.  Not used.
	 * @throws IOException if there are errors in the input.
	 */
	public static void  main(String[]  args) throws IOException  {

		Catalog catalog  = load();

		LibrarySystem  app = new  LibrarySystem(catalog, load(catalog));

		app.run();

	}

	/*
	 * Loads the information of a Catalog object.
	 */
	private static Catalog load ()  {

		Catalog catalog = new Catalog();

		catalog.addItem(new Book("B001", "Effective Java Programming", 2001,
		                         "Joshua Bloch", 252));
		catalog.addItem(new Book("B002", "Design Patterns", 1995,
		                         "Erich Gamma et al", 395));
		catalog.addItem(new Book("B003", "Refactoring", 1999,
		                         "Martin Fowler", 431));
		catalog.addItem(new Book("B004", "The Mythical Man-Month", 1995,
		                         "Frederick P. Brooks", 322));
		catalog.addItem(new Book("B005", "Code Complete", 1993,
		                         "Steve C McConnell", 857));
		catalog.addItem(new Book("B006", "The Psychology of Comp. Progr.", 1998,
		                         "Gerald M. Weinberg", 360));
		catalog.addItem(new Book("B007", "Programming Pearls ", 1999,
		                         "Jon Bentley", 239));
		catalog.addItem(new Book("B008", "The Practice of Programming", 1999,
		                         "Brian W. Kernighan", 257));
		catalog.addItem(new Book("B009", "Peopleware", 1999,
		                         "Tom Demarco", 245));
		catalog.addItem(new Book("B010", "The Java Programming Language", 2000,
		                         "Ken Arnold", 595));
		catalog.addItem(new Book("B011", "Core J2EE Patterns", 2001,
		                         "Deepak Alur", 496));
		catalog.addItem(new Book("B012", "Rapid Development", 1996,
		                         "Steve C McConnell", 680));
		catalog.addItem(new Book("B013", "Applying UML and Patterns", 2001,
		                         "Craig Larman", 656));
		catalog.addItem(new Book("B014", "The Little Schemer", 1995,
		                         "Daniel P. Friedman", 216));
		catalog.addItem(new Book("B015", "Agile Software Development", 2001,
		                         "Alistair Cockburn", 256));

		catalog.addItem(new Recording("R001", "Getz/Gilberto", 1963,
		                              "Stan Getz and Joao Gilberto", "CD"));
		catalog.addItem(new Recording("R002", "Kind of Blue", 1997,
		                              "Miles Davis", "CD"));
		catalog.addItem(new Recording("R003", "Supernatural", 1999,
		                              "Santana", "Tape"));
		catalog.addItem(new Recording("R004", "Private Collection", 1983,
		                              "Jon & Vangelis", "Tape"));
		catalog.addItem(new Recording("R005", "Abbey Road", 1969,
		                              "Beatles", "CD"));
		catalog.addItem(new Recording("R006", "Joshua Tree", 1990,
		                              "U2", "CD"));

		return catalog;
	}

	/*
	 * Loads a BorrowerDatabase object.
	 */
	private static BorrowerDatabase load(Catalog catalog) {

		BorrowerDatabase borrowerDB = new BorrowerDatabase();

		Borrower borrower = new Borrower("ID001", "James Addy");

		borrower.getBorrowedItems().addItem(catalog.getItem("B003"));
		borrower.getBorrowedItems().addItem(catalog.getItem("R001"));
		borrower.getBorrowedItems().addItem(catalog.getItem("B012"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID002", "John Doust");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID003", "Constance Foster");
		borrower.getBorrowedItems().addItem(catalog.getItem("B006"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID004", "Harold Gurske");
		borrower.getBorrowedItems().addItem(catalog.getItem("B002"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID005", "Mary A. Rogers");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID006", "Laura Novelle");
		borrower.getBorrowedItems().addItem(catalog.getItem("B007"));
		borrower.getBorrowedItems().addItem(catalog.getItem("B009"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID007", "David M. Prescott");
		borrower.getBorrowedItems().addItem(catalog.getItem("B011"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID008", "Francis Matthews");
		borrower.getBorrowedItems().addItem(catalog.getItem("R003"));
		borrower.getBorrowedItems().addItem(catalog.getItem("B005"));
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID009", "Thomas Ferris");
		borrowerDB.addBorrower(borrower);

		borrower = new Borrower("ID010", "John Johnson");
		borrower.getBorrowedItems().addItem(catalog.getItem("B004"));
		borrowerDB.addBorrower(borrower);

		return borrowerDB;
	}

	/*
	 * Constructs a <code>LibrarySystem</code> object.
	 * Initialize the catalog and the borrower database with
	 * the values specified in the parameters.
	 */
	private LibrarySystem(Catalog initialCatalog,
	                      BorrowerDatabase initialBorrowerDB) {

		this.catalog = initialCatalog;
		this.borrowerDB = initialBorrowerDB;
	}

	/*
	 * Presents the user with a menu of options and processes the selection.
	 */
	private void run() throws IOException  {

		int  choice = getChoice();

		while (choice != 0)  {

			if (choice == 1)  {
				displayCatalog();
			} else if (choice == 2)  {
				displayCatalogItem();
			} else if (choice == 3)  {
				displayBorrowerDatabase();
			} else if (choice == 4)  {
				displayBorrower();
			} else if (choice == 5)  {
				checkOut();
			} else if (choice == 6)  {
				checkIn();
			}

			choice = getChoice();
		}
	}

	/* Validates the user's choice. */
	private int  getChoice() throws IOException  {

		int  input;

		do  {
			try  {
				stdErr.println();
				stdErr.print("[0]  Quit\n"
				             + "[1]  Display catalog\n"
				             + "[2]  Display catalog item\n"
				             + "[3]  Display borrowers\n"
				             + "[4]  Display borrowed items\n"
				             + "[5]  Check out\n"
				             + "[6]  Check in\n"
				             + "choice> ");
				stdErr.flush();

				input = Integer.parseInt(stdIn.readLine());

				stdErr.println();

				if (0 <= input && 6 >= input)  {
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

	/*
	 * Displays the catalog.
	 */
	private void displayCatalog() {

		/*
		if (this.catalog.getNumberOfItems() == 0) {
			stdErr.println("The catalog is empty");
		} else {
			
			for (CatalogItem item : this.catalog) {
				stdOut.println(item.getCode() + " " + item.getTitle() + " "
				               + (item.isAvailable()? "(A)" : "(NA)"));
			}
		*/
		if (this.catalog.getNumberOfItems() == 0) {
				stdErr.println("The catalog is empty");
		} else {
			 Iterator<CatalogItem> iterator = this.catalog.iterator();
			 for(;iterator.hasNext();) {
			 	CatalogItem item = iterator.next();
			 	stdOut.println(item.getCode() + " " + item.getTitle() + " "
				               + (item.isAvailable()? "(A)" : "(NA)"));
			 }
			 
		}
	}

	/*
	 * Displays a catalog item.
	 */
	private void displayCatalogItem()  throws IOException  {

		CatalogItem item = readCatalogItem();

		if (item != null) {
			stdOut.println("  Title: " + item.getTitle());
			stdOut.println("  Year: " + item.getYear());
			if (item instanceof Book) {

				Book book = (Book) item;

				stdOut.println("  Author: " + book.getAuthor());
				stdOut.println("  Number of pages: " + book.getNumberOfPages());
			} else if (item instanceof Recording) {

				Recording recording = (Recording) item;

				stdOut.println("  Performer: " + recording.getPerformer());
				stdOut.println("  Format: " + recording.getFormat());
			}
			stdOut.println(
				"  Status: "
				+ (item.isAvailable() ? "Available" : "Not available"));
		} else {
			stdErr.println("There is no catalog item with that code");
		}
	}

	/*
	 * Displays the borrower database.
	 */
	private void displayBorrowerDatabase() {

		if (this.borrowerDB.getNumberOfBorrowers() == 0) {
			stdErr.println("The database of borrowers is empty");
		} else {
			for (Borrower borrower : this.borrowerDB) {
				stdOut.println(borrower.getId() + " " + borrower.getName());
			}
		}
	}

	/*
	 * Displays a borrower.
	 */
	private void displayBorrower()  throws IOException  {

		Borrower borrower = readBorrower();

		if (borrower != null) {

			stdOut.println("  Name: " + borrower.getName());

			BorrowedItems borrowedItems = borrower.getBorrowedItems();

			if (borrowedItems.getNumberOfItems() == 0) {
				stdOut.println("  No items borrowed");
			} else {
				stdOut.println("  Items Borrowed:");
				for (CatalogItem item : borrowedItems) {
					stdOut.println(
						"    " + item.getCode() + " " + item.getTitle());
				}
			}
		} else {
			stdErr.println("There is no borrower with that id");
		}
	}

	/*
	 * Registers the loan of a item to a borrower.
	 */
	private void checkOut()  throws IOException  {

		CatalogItem item = readCatalogItem();

		if (item == null) {
			stdErr.println("There is no catalog item with that code");
		} else if (item.isAvailable()) {

			Borrower borrower = readBorrower();

			if (borrower == null) {
				stdErr.println("There is no borrower with that id");
			} else {
				borrower.getBorrowedItems().addItem(item);
				stdOut.println("The item " + item.getCode()
				               + " has been check out by " + borrower.getId());
			}
		} else {
			stdErr.println("The item " +  item.getCode() +
			               " is not available");
		}
	}

	/*
	 * Registers the return of a item.
	 */
	private void checkIn()  throws IOException  {

		CatalogItem item = readCatalogItem();

		if (item == null) {
			stdErr.println(
				"There is no catalog item with that code");
		} else if (item.isAvailable()) {
			stdErr.println("The item " +  item.getCode() + " is not borrowed");
		} else {

			Borrower borrower = readBorrower();

			if (borrower == null) {
				stdErr.println("There is no borrower with that id");
			} else {
				borrower.getBorrowedItems().removeItem(item);
				stdOut.println("The item " +  item.getCode()
				               + " has been returned");
			}
		}
	}

	/*
	 * Obtains a CatalogItem object  .
	 */
	private  CatalogItem readCatalogItem() throws IOException  {

		stdErr.print("Catalog item code> ");
		stdErr.flush();

		return this.catalog.getItem(stdIn.readLine());
	}

	/*
	 * Obtains a Borrower object  .
	 */
	private  Borrower readBorrower()  throws IOException  {

		stdErr.print("Borrower id> ");
		stdErr.flush();

		return this.borrowerDB.getBorrower(stdIn.readLine());
	}
}
/*!End Snippet:file*/
