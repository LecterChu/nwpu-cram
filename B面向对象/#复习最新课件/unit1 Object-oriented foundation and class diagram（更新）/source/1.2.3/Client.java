/*!Begin Snippet:file*/
import  java.util.*;

/**
 * This class models a bank client. The following information is maintained:
 * <ol>
 * <li>The name of the client</li>
 * <li>The bank accounts of the client</li>
 * </ol>
 *
 * @author iCarnegie
 * @version  1.0.0
 */
public class Client { //implements Iterable<BankAccount> 

	/* Name of client */
	private String name;

	/* Collection of <code>BankAccounts</code> objects.*/
	private ArrayList<BankAccount>  bankAccounts;

	/**
	 * Constructs a <code>Client</code> object.
	 * <p>
	 * Creates an empty collection of bank accounts.
	 * </p>
	 *
	 * @param initialName  the name of the client.
	 */
	public Client(String initialName)  {

		this.name = initialName;
		this.accounts = new                       ArrayList<BankAccount>();
	}

	/**
	 * Returns the name of this client.
	 *
	 * @return the name of this client.
	 */
	public String  getName() {

		return this.name;
	}

	/**
	 * Adds a bank account to this client.
	 *
	 * @param bankAccount  the {@link BankAccount} object.
	 */
	public void  addAccount(BankAccount bankAccount)  {

		this.accounts.add(bankAccount);
	}

	/**
	 * Returns an iterator over the bank accounts of this client.
	 *
	 * return  an {@link Iterator} over the bank accounts of this
	 *         client.
	 */
	public Iterator<BankAccount>  iterator() {

		return this.accounts.iterator();
	}

	/**
	 * Returns the number of bank account of this client.
	 *
	 * @return  the number of bank account of this client.
	 */
	public int  getNumberOfAccounts()  {

		return this.accounts.size();
	}	
	
}

/*!End Snippet:file*/