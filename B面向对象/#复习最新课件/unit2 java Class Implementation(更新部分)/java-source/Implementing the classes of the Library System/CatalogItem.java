/**
 * This class models a catalog item. 
 * It contains the following
 * following information:
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
	 * @param initialCode  the code of the item.
	 * @param initialTitle  the title of the item.
	 * @param initialyear  the year the item was published.
	 */
	public CatalogItem(String initialCode, 
			String initialTitle,
			int initialyear) {

		this.code = initialCode;
		this.title = initialTitle;
		this.year = initialyear;
		this.available = true;
	}

	/**
	 * Returns the code of this item.
	 * @return  the code of this item.
	 */
	public String  getCode()  {

		return  this.code;
	}

	/**
	 * Returns the title of this item.
	 * @return  the title of this item.
	 */
	public String  getTitle()  {

		return  this.title;
	}

	/**
	 * Returns the year this item was published.
	 * @return  the year this item was published.
	 */
	public int  getYear()  {

		return  this.year;
	}

	/**
	 * Sets the value of instance variable 
	 * <code>available</code>.
	 * @param value  the new value.
	 */
	public void  setAvailable(boolean value)  {

		this.available = value;
	}

	/**
	 * Returns <code>true</code> if the item 
	 * is available.
	 * @return  <code>true</code> if the item 
	 * is available;
	 *          <code>false</code> otherwise.
	 */
	public boolean  isAvailable()  {

		return this.available;
	}

}