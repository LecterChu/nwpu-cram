/*!Begin Snippet:file*/
/**
 * This class models a catalog item. It contains the following
 * following information:
 * </p>
 * <ol>
 * <li>the code of the item, a <code>String</code></li>
 * <li>the title of the item, a <code>String</code></li>
 * <li>the year the item was published, an <code>int</code></li>
 * <li>a <code>boolean</code> value that indicates if the item is
 *     available</li>
 * </ol>
 *
 * @author iCarnegie
 * @version  1.0.0
 */
public class CatalogItem {

	/* Code of the item. */
	private String  code;

	/* Title of the item. */
	private String  title;

	/* Year the item was published. */
	private int  year;

	/* Indicates if the item is available */
	private boolean  available;

	/**
	 * Constructs a <code>CatalogItem</code> object.
	 * <p>
	 * Sets the instance variable <code>available</code>
	 * to <code>true</code>.
	 * <p>
	 *
	 * @param initialCode  the code of the item.
	 * @param initialTitle  the title of the item.
	 * @param initialyear  the year the item was published.
	 */
	public CatalogItem(String initialCode, String initialTitle,
			int initialyear) {

		this.code = initialCode;
		this.title = initialTitle;
		this.year = initialyear;
		this.available = true;
	}

	/**
	 * Returns the code of this item.
	 *
	 * @return  the code of this item.
	 */
	public String  getCode()  {

		return  this.code;
	}

	/**
	 * Returns the title of this item.
	 *
	 * @return  the title of this item.
	 */
	public String  getTitle()  {

		return  this.title;
	}

	/**
	 * Returns the year this item was published.
	 *
	 * @return  the year this item was published.
	 */
	public int  getYear()  {

		return  this.year;
	}

	/**
	 * Sets the value of instance variable <code>available</code>.
	 *
	 * @param value  the new value.
	 */
	public void  setAvailable(boolean value)  {

		this.available = value;
	}

	/**
	 * Returns <code>true</code> if the item is available.
	 *
	 * @return  <code>true</code> if the item is available;
	 *          <code>false</code> otherwise.
	 */
	public boolean  isAvailable()  {

		return this.available;
	}

	/**
	 * Returns <code>true</code> if the code of this catalog item is
	 * equal to the code of the argument
	 *
	 * @param object  object with which this catalog item is compared.
	 * @return  <code>true</code> if the code of this catalog item is
	 *          equal to the code of the argument; <code>false</code>
	 *          otherwise.
	 */
	public boolean  equals(Object  object)  {

		return object instanceof CatalogItem
		       && getCode().equals(((CatalogItem) object).getCode());
	}

	/**
	 * Returns the string representation of this catalog item.
	 *
	 * @return  the string representation of this catalog item.
	 */
	public String toString()  {

		return  getCode() + "_" + getTitle() + "_" + getYear()
		        + "_" + isAvailable();
	}
}
/*!End Snippet:file*/