/*!Begin Snippet:file*/
/**
 * This class models a library user. It contains the following
 * information:
 * <ol>
 * <li>The id of the borrower, a <code>String</code></li>
 * <li>The name of the borrower, a <code>String</code></li>
 * <li>The items checked out by the borrower,
 *     a <code>BorrowedItems</code> object</li>
 * </ol>
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see BorrowedItems
 * @see CatalogItem
 */
public class Borrower {

	/* Identification number of the borrower.*/
	private String  id;

	/* Name of the borrower.*/
	private String  name;

	/* Items checked out by the borrower.*/
	private BorrowedItems  borrowedItems;

	/**
	 * Constructs a <code>Borrower</code> object.
	 * <p>
	 * The collection of the borrowed items is initially empty.
	 * </p>
	 *
	 * @param initialId  the id of the borrower.
	 * @param initialName  the name of the borrower.
	 */
	public Borrower(String initialId, String initialName)  {

		this.id = initialId;
		this.name = initialName;
		this.borrowedItems = new BorrowedItems();
	}

	/**
	 * Returns the identification number of this borrower.
	 *
	 * @return  the identification number of this borrower.
	 */
	public String  getId()  {

		return  this.id;
	}

	/**
	 * Returns the name of this borrower.
	 *
	 * @return  the name of this borrower.
	 */
	public String  getName () {

		return  this.name;
	}

	/**
	 * Returns the borrowed items collection.
	 *
	 * @return  a {@link BorrowedItems} object.
	 */
	public BorrowedItems  getBorrowedItems () {

		return  this.borrowedItems;
	}

	/**
	 * Returns <code>true</code> if the id of this borrower is
	 * equal to the id of the argument.
	 *
	 * @param object  object with which this borrower is compared.
	 * @return  <code>true</code> if the id of this borrower is
	 *          equal to the id of the argument; <code>false</code>
	 *          otherwise.
	 */
	public boolean  equals(Object  object)  {

		return object instanceof Borrower
		       && getId().equals(((Borrower) object).getId());
	}

	/**
	 * Returns the string representation of this borrower.
	 *
	 * @return  the string representation of this borrower.
	 */
	public String  toString()  {

		return  getId() + "_" + getName();
	}
}
/*!End Snippet:file*/