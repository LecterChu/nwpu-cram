/*!Begin Snippet:file*/
/**
 * This class models an employee.
 *
 * @author author name
 * @version 1.0.0
 * @see Person
 */
public class  Employee  extends  Person  {

	/* The age of the employee */
	private int  age;

	/**
	 * Constructs an <code>Employee</code> object.
	 *
	 * @param initialName  the name of this employee.
	 * @param initialAge  the age of this employee.
	 */
	 public Employee(String initialName,
	 	int initialAge) {

	 	super(initialName);

	 	age = initialAge;
	 }

	/**
	 * Obtains the age of this employee.
	 *
	 * @return the age of this employee.
	 */
	public int  getAge() {

		return age;
	}
	public String toString() {
		
		return "Employee---"+"name: "+getName()+" | age: "+age;		
	}
}
/*!End Snippet:file*/