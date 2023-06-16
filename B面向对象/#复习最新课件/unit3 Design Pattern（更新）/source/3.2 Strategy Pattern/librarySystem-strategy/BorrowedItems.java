/*!Begin Snippet:file*/
import java.util.*;
import java.text.*;

/**
 * Maintains a collection of {@link CatalogItem} assigned to a borrower.
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see CatalogItem
 */
public class BorrowedItems implements Iterable<CatalogItem>  {

	/* Catalog items assigned to a borrower.*/
	private ArrayList<CatalogItem>  items;

	/**
	 * Sets the collection of {@link CatalogItem} to empty.
	 */
	public BorrowedItems()  {

		this.items = new ArrayList<CatalogItem>();
	}

	/**
	 * Adds a {@link CatalogItem} object to this collection and
	 * sets the {@link CatalogItem} object as not available.
	 *
	 * @param catalogItem  the {@link CatalogItem} object.
	 */
	public void  addItem(CatalogItem catalogItem)  {

		this.items.add(catalogItem);
		catalogItem.setAvailable(false);
	}

	/**
	 * Removes a {@link CatalogItem} object from this collection
	 * and sets the {@link CatalogItem} object as available.
	 *
	 * @param catalogItem  the {@link CatalogItem} object.
	 */
	public void  removeItem(CatalogItem catalogItem)  {

		this.items.remove(catalogItem);
		catalogItem.setAvailable(true);
	}

	/**
	 * Returns an iterator over the borrowed items in this collection.
	 *
	 * return  an {@link Iterator} of {@link CatalogItem}
	 */
	public Iterator<CatalogItem> iterator() {

		return this.items.iterator();
	}

	/**
	 * Returns the {@link CatalogItem} object with the specified
	 * <code>code</code>.
	 *
	 * @param code  the code of an item.
	 * @return  The {@link CatalogItem} object with the specified
	 *          code. Returns <code>null</code> if the object with
	 *          the code is not found.
	 */
	public CatalogItem  getItem(String code)  {

		for (CatalogItem catalogItem : this.items) {
			if (catalogItem.getCode().equals(code)) {

				return catalogItem;
			}
		}

		return null;
	}

	/**
	 * Returns the number of borrowed items.
	 *
	 * @return  the number of borrowed items.
	 */
	public int  getNumberOfItems()  {

		return this.items.size();
	}
}

/*!End Snippet:file*/