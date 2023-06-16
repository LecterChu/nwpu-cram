/*!Begin Snippet:file*/
import java.util.*;
import java.io.*;

/**
 * Creates a library catalog and loads it with data stored in
 * a file.
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see LibraryCatalogLoader
 * @see Catalog
 * @see CatalogItem
 * @see Recording
 * @see Book
 */
public class FileLibraryCatalogLoader implements LibraryCatalogLoader  {

	/* Prefix of a line with book data */
	private final static String BOOK_PREFIX = "Book";

	/* Prefix of a line with recording data */
	private final static String RECORDING_PREFIX = "Recording";

	/* Delimiter */
	private final static String DELIM = "_";

	/**
	 * Loads the information in the specified file into a library
	 * catalog and returns the catalog.
	 *
	 * @param filename  The name of a file that contains catalog
	 *                  information.
	 * @return a library catalog.
	 * @throws IOException if there is an error reading the
	 *                     information in the specified file.
	 * @throws FileNotFoundException  if the specified file does not
	 *                                exist.
	 * @throws DataFormatException if the file contains malformed
	 *                             data.
	 */
	public Catalog loadCatalog (String filename) throws IOException,
			FileNotFoundException, DataFormatException {

		Catalog catalog = new Catalog();

		BufferedReader reader =
			new BufferedReader(new FileReader(filename));
		String line =  reader.readLine();

		while (line != null) {

			CatalogItem item = null;

			if (line.startsWith(BOOK_PREFIX)) {
				item = readBook(line);
			} else if (line.startsWith(RECORDING_PREFIX)) {
				item = readRecording(line);
			} else {

				throw new DataFormatException(line);
			}

			catalog.addItem(item);

			line =  reader.readLine();
		}

		reader.close();

		return catalog;
	}

	/**
	 * Extracts the book data in the specified line and returns
	 * a {@link Book} object that encapsulates the book data.
	 *
	 * @param line  a string that contains book data.
	 * @return  a <code>Book</code> object that encapsulates the
	 *          book data in the specified line.
	 * @throws DataFormatException if the line contains errors.
	 */
	private Book readBook (String line) throws DataFormatException {

		StringTokenizer tokenizer = new StringTokenizer(line, DELIM);

		if (tokenizer.countTokens() != 6) {

			throw new DataFormatException(line);
		} else {
			try {

				String prefix = tokenizer.nextToken();

				return new  Book (tokenizer.nextToken(),
					tokenizer.nextToken(),
					Integer.parseInt(tokenizer.nextToken()),
					tokenizer.nextToken(),
					Integer.parseInt(tokenizer.nextToken()));

			} catch (NumberFormatException  nfe)  {

				throw new DataFormatException(line);
			}
		}
	}

	/**
	 * Extracts the recording data in the specified line and returns
	 * a {@link Recording} object that encapsulates the book data.
	 *
	 * @param line  a string that contains recording data.
	 * @return  a <code>Recording</code> object that encapsulates the
	 *          recording data in the specified line.
	 * @throws DataFormatException if the line contains errors.
	 */
	private Recording readRecording (String line)
		throws DataFormatException {

		StringTokenizer tokenizer =	new StringTokenizer(line, DELIM);

		if (tokenizer.countTokens() != 6) {

			throw new DataFormatException(line);
		} else {
			try {

				String prefix = tokenizer.nextToken();

				return new Recording (tokenizer.nextToken(),
					tokenizer.nextToken(),
					Integer.parseInt(
						tokenizer.nextToken()),
					tokenizer.nextToken(),
					tokenizer.nextToken());

			} catch (NumberFormatException  nfe)  {

				throw new DataFormatException(line);
			}
		}
	}
}
/*!End Snippet:file*/