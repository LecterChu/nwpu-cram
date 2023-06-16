/*!Begin Snippet:file*/
import java.util.*;
import java.text.*;

/**
 * Maintains a collection of {@link Borrower} objects.
 *
 * @author iCarnegie
 * @version  1.0.0
 * @see Borrower
 */
public class BorrowerDatabase implements Iterable<Borrower> {

	/* Collection of <code>Borrower</code> objects.*/
	private ArrayList<Borrower>  borrowers;

	/**
	 * Constructs an empty collection of {@link Borrower}
	 * objects.
	 */
	public BorrowerDatabase()  {

		this.borrowers = new ArrayList<Borrower>();
	}

	/**
	 * Adds a {@link Borrower} object to this collection.
	 *
	 * @param borrower  the {@link Borrower} object.
	 */
	public void  addBorrower(Borrower borrower)  {

		this.borrowers.add(borrower);
	}

	/**
	 * Returns an iterator over the borrowers in this database.
	 *
	 * return  an {@link Iterator} of {@link Borrower}
	 */
	public Iterator<Borrower>  iterator() {

		return this.borrowers.iterator();
	}

	/**
	 * Returns the {@link Borrower} object with the specified
	 * <code>id</code>.
	 *
	 * @param id  the id of the borrower.
	 * @return  The {@link Borrower} object with the specified id.
	 *          Returns <code>null</code> if the object with the
	 *          id is not found.
	 */
	public Borrower  getBorrower(String id)  {

		for (Borrower borrower : this.borrowers) {
			if (borrower.getId().equals(id)) {

				return borrower;
			}
		}

		return null;
	}

	/**
	 * Returns the number of {@link Borrower} objects in this collection.
	 *
	 * @return  the number of {@link Borrower} objects in this collection.
	 */
	public int  getNumberOfBorrowers()  {

		return this.borrowers.size();
	}
}
/*!End Snippet:file*/
