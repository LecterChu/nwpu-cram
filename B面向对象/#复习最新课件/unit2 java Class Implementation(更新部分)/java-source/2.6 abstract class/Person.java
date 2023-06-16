/*!Begin Snippet:file*/
/**
 * This class models a person.
 *
 * @author author name
 * @version 1.0.0
 */
public abstract class Person {

	/* the name of the person */
	private String name;

	/**
	 * Constructs a <code>Person</code> object.
	 *
	 * @param initialName  the name of this person.
	 */
	public Person(String initialName) {

		name = initialName;
	}

	/**
	 * Obtains the name of this person.
	 *
	 * @return the name of this person.
	 */
	public String  getName() {

		return name;
	}
	public String toString() {
		
		return "Person---"+"name: "+name;
	}
}
/*!End Snippet:file*/