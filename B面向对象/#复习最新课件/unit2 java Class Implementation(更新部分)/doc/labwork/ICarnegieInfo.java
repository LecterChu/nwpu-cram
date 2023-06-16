/*!Begin Snippet:file*/
/**
 * This class is a singleton that contains the contact
 * information for <cite>iCarnegie</cite>.
 *
 * @author author name
 * @version  1.0.0
 */
public class ICarnegieInfo  {

	static private ICarnegieInfo singletonInstance = null;

	private String name;
	private String address;
	private String telephone;

	/*
	 * Initializes the instance variables. The constructor is
	 * declared private so it can only be called by methods of this
	 * class. This prevents other classes from creating more
	 * instances.
	 */
	private ICarnegieInfo () {

		name = "iCarnegie, Inc";
		address = "4615 Forbes Avenue Pittsburgh, PA 15213-3796";
		telephone = "1.412.622.2150";
	}

	/**
	 * Obtains the single instance of class
	 * <code>ICarnegieInfo</code>
	 *
	 * @return the single instance  of class
	 *         <code>ICarnegieInfo</code>
	 */
	static public ICarnegieInfo getSingletonInstance() {

		if (singletonInstance == null) {
			singletonInstance = new ICarnegieInfo();
		}

		return singletonInstance;
	}

	/**
	 * Obtains the name of <cite>iCarnegie</cite>
	 *
	 * @return  a string with the name of <cite>iCarnegie</cite>
	 */
	public String getName() {

		return name;
	}

	/**
	 * Obtains the address of <cite>iCarnegie</cite>
	 *
	 * @return  a string with the address of <cite>iCarnegie</cite>
	 */
	public String getAddress() {

		return address;
	}

	/**
	 * Obtains the telephone of <cite>iCarnegie</cite>
	 *
	 * @return  a string with the telephone of <cite>iCarnegie</cite>
	 */
	public String getTelephone() {

		return telephone;
	}
}
/*!End Snippet:file*/