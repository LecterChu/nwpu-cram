/*!Begin Snippet:file*/
/**
 * This class models a book. It extends {@link CatalogItem} and
 * adds the following information:
 * <ol>
 * <li>the author of the book, a <code>String</code></li>
 * <li>the number of pages in the book, an <code>int</code></li>
 * </ol>
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see CatalogItem
 */
public class Book extends CatalogItem  {

	/* Author of the book.*/
	private String  author;

	/* Number of pages in the book.*/
	private int  numberOfPages;

	/**
	 * Constructs a <code>Book</code> object.
	 *
	 * @param initialCode  the code of the book.
	 * @param initialTitle  the title of the book.
	 * @param initialYear  the year the book was published.
	 * @param initialAuthor  the author of the book.
	 * @param initialNumberOfPages  the number of pages in the book.
	 */
	public Book(String initialCode, String initialTitle,
	 		int initialYear, String initialAuthor,
			int initialNumberOfPages) {

		super(initialCode, initialTitle, initialYear);

		this.author = initialAuthor;
		this.numberOfPages = initialNumberOfPages;
	}

	/**
	 * Returns the author of this book.
	 *
	 * @return  the author of this book.
	 */
	public String  getAuthor()  {

		return  this.author;
	}

	/**
	 * Returns the number of pages in this book.
	 *
	 * @return  the number of pages in this book.
	 */
	public int  getNumberOfPages()  {

		return  this.numberOfPages;
	}

	/**
	 * Returns the string representation of this book.
	 *
	 * @return  the string representation of this book.
	 */
	public String toString()  {

		return  super.toString() + "_" + getAuthor() + "_"
		        + getNumberOfPages();
	}
}
/*!End Snippet:file*/