/*!Begin Snippet:file*/
/**
 * This class models a client.
 *
 * @author author name
 * @version 1.0.0
 * @see Person
 */
public class  Client  extends  Person  {

	/* The credit of the client */
	private double  credit;

	/**
	 * Constructs a <code>Client</code> object.
	 *
	 * @param initialName  the name of this client.
	 * @param initialCredit  the credit of this client.
	 */
	 public Client(String initialName,
		double initialCredit) {

	 	super(initialName);

	 	credit = initialCredit;
	 }

	/**
	 * Obtains the credit of this client.
	 *
	 * @return the credit of this client.
	 */
	public double  getCredit() {

		return credit;
	}
	public String toString() {
		
		return "Client---"+"name: "+getName()+" | credit: "+credit;
	}
}
/*!End Snippet:file*/