/*!Begin Snippet:file*/
import java.io.*;
import java.util.*;

/**
 * This class implements a sample of the library system.
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
 * @see LibraryCatalogLoader
 * @see FileLibraryCatalogLoader
 */
public class LibrarySystem  {

	private static BufferedReader  stdIn =
			new  BufferedReader(new  InputStreamReader(System.in));
	private static PrintWriter  stdOut =
			new  PrintWriter(System.out, true);
	private static PrintWriter  stdErr =
			new  PrintWriter(System.err, true);

	private Catalog  catalog;

	private BorrowerDatabase borrowerDB;

	private BorrowersFormatter borrowersFormatter;

	/**
	 * Loads a library catalog and borrower database from a file
	 * and then starts the application.
	 * <p>
	 * The name of the file is specified in the command arguments
	 * </p>
	 *
	 * @param args  String arguments.
	 * @throws IOException if there are errors in the input.
	 */
	public static void  main(String[]  args) throws IOException {

		if (args.length != 1) {
			stdErr.println("Usage: java LibrarySystem filename");
		} else {

			Catalog catalog = null;

			try {

				LibraryCatalogLoader loader =
						new FileLibraryCatalogLoader();

				catalog = loader.loadCatalog(args[0]);
			} catch (FileNotFoundException fnfe) {
				stdErr.println("The file does not exist");

				System.exit(1);

			} catch (DataFormatException dfe) {
				stdErr.println("The file contains malformed data: "
				               + dfe.getMessage());

				System.exit(1);
			}

			LibrarySystem  app = new LibrarySystem(catalog);

			app.run();
		}
	}

	/*
	 * Constructs a <code>LibrarySystem</code> object.
	 * Initialize the catalog and borrower database with
	 * the values specified in the parameter.
	 */
	private LibrarySystem(Catalog initialCatalog) {

		catalog = initialCatalog;
		borrowerDB = loadBorrowers(catalog);
		borrowersFormatter =
				PlainTextBorrowersFormatter.getSingletonInstance();
	}

	/*
	 * Loads a BorrowerDatabase object.
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

	/*
	 * Presents user with menu of options and executes selected task.
	 */
	private void run() throws IOException  {

		int  choice = getChoice();

		while (choice != 0)  {
			if (choice == 1)  {
				displayCatalog();
			} else if (choice == 2)  {
				this.borrowersFormatter =
					PlainTextBorrowersFormatter.getSingletonInstance();
				writeFile(readFileName(),
					this.borrowersFormatter.formatBorrowers(this.borrowerDB));
			} else if (choice == 3)  {
				this.borrowersFormatter =
					HTMLBorrowersFormatter.getSingletonInstance();
				writeFile(readFileName(),
					this.borrowersFormatter.formatBorrowers(this.borrowerDB));
			} else if (choice == 4)  {
				this.borrowersFormatter =
					XMLBorrowersFormatter.getSingletonInstance();
				writeFile(readFileName(),
					this.borrowersFormatter.formatBorrowers(this.borrowerDB));
			}

			choice = getChoice();
		}
	}

	/*
	 * Displays a menu of options and verifies the user's choice.
	 */
	private int  getChoice() throws IOException  {

		int  input;

		do  {
			try  {
				stdErr.println();
				stdErr.print("[0]  Quit\n"
				             + "[1]  Display catalog\n"
				             + "[2]  Save borrower database (plain text)\n"
				             + "[3]  Save borrower database (HTML)\n"
				             + "[4]  Save borrower database (XML)\n"
				             + "choice> ");
				stdErr.flush();

				input = Integer.parseInt(stdIn.readLine());

				stdErr.println();

				if (0 <= input && 4 >= input)  {
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

		int numberOfItems = this.catalog.getNumberOfItems();

		if (numberOfItems == 0) {
			stdErr.println("The catalog is empty");
		} else {
			for (CatalogItem item : this.catalog) {
				stdOut.println(item.getCode() + " "
						+ item.getTitle() + " " +
						(item.isAvailable()? "(A)" : "(NA)"));
			}
		}
	}

	/*
	 * Prompts the user for a file name (the name of the file that
	 * will store the borrower database) and returns the user's
	 * response.
	 */
	private  String readFileName() throws IOException  {

		stdErr.print("File name> ");
		stdErr.flush();

		return stdIn.readLine();
	}

	/*
	 * Creates a new file (which has the specified name) and writes
	 * the specified string to the new file
	 */
	private void writeFile(String fileName, String content)
			throws IOException {

		PrintWriter fileOut =
				new PrintWriter(new FileWriter(fileName));

		fileOut.println(content);

		fileOut.close();
	}
}
/*!End Snippet:file*/