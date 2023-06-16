public class LibrarySystem{
	...
	private BorrowerDatabase borrowerDB;
	...
	public static void  main(String[]  args) throws IOException {

		LibrarySystem  app = new  LibrarySystem();

		app.run();
	}

	...
			
	public String formatBorrowers (String strFormat) {
		
		String out;
		
		if (strFormat.equals("plain text")) {
			
			
			out = "Borrower Database" + NEW_LINE;

			for (Iterator i = borrowerDB.getBorrowersIterator(); i.hasNext();) {

				Borrower borrower = (Borrower) i.next();
	
				out += borrower.getId() + "_" + borrower.getName();
	
				BorrowedItems items = borrower.getBorrowedItems();
	
				for (Iterator j = items.getItemsIterator();
					j.hasNext();) {
	
					out += "_" + ((CatalogItem) j.next()).getCode();
				}
			out += NEW_LINE;
		}

					
		} else if (strFormat.equals("HTML")) {
			
			String out = "<html>"
				+ NEW_LINE
				+ "  <body>"
				+ NEW_LINE + ""
				+ "    <center><h2>Borrower Database</h2></center>"
				+ NEW_LINE;
	
			for (Iterator i = borrowerDB.getBorrowersIterator();
				i.hasNext();) {
	
				Borrower borrower = (Borrower) i.next();
	
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
	
					for (Iterator j = items.getItemsIterator();
						 j.hasNext();) {
	
						CatalogItem item = (CatalogItem) j.next();
	
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
						
			
		} else if (strFormat.equals("XML")) {
			
			out= ...;
			
			out = "<BorrowerDatabase>" + NEW_LINE ;

			for (Iterator i = borrowerDB.getBorrowersIterator(); i.hasNext();) {

				Borrower borrower = (Borrower) i.next();
	
				out += "  <Borrower id=\""
					+ borrower.getId()
					+ "\" name=\"" 
					+ borrower.getName()
					+ "\">"
					+ NEW_LINE;
	
				BorrowedItems items = borrower.getBorrowedItems();
	
				if (items.getNumberOfItems() > 0) {
					out += "    <BorrowedItems>" + NEW_LINE;
	
					for (Iterator j = items.getItemsIterator();
						 j.hasNext();) {
	
						CatalogItem item = (CatalogItem) j.next();
	
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
					
		}	
		
		return out;
	}
	
	
	private void run() throws IOException  {

		int  choice = getChoice();

		while (choice != 0)  {

			if (choice == 1)  {
				String out = app.formatBorrowers("plain text",borrowerDB);
				...				
			} else if (choice == 2)  {
				app.formatBorrowers("HTML",borrowerDB);
				...
			} else if (choice == 3)  {
				app.formatBorrowers("XML",borrowerDB);
				...
			}
			...			
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
}
