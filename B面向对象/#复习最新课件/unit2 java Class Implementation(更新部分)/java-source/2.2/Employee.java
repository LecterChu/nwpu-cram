/**
 * This class models an Employee.
 *
 * @author author name
 * @version 1.0.0
 */
public class Employee extends Person {

	/* Salary of the employee */
	private double salary;

	/**
	 * Constructs an <code>Employee</code> object.
	 *
	 * @param initialName  the name of the employee.
	 * @param initialAddress  the address of the employee.
	 * @param initialSalary  the salary of the employee.
	 */
	public Employee(String initialName, String initialAddress,
			double initialSalary) {

		super(initialName, initialAddress);
		//name = initialName;
		//address = initialAddress;
		salary = initialSalary;
	}

	/*
	 public Employee (double initialSalary) {

	 salary = initialSalary;
	 }
	 */
	/**
	 * Returns the salary of this employee.
	 *
	 * @return the salary of this employee.
	 */
	public double getSalary() {

		return salary;
	}

	/**
	 * Modifies the salary of this employee.
	 *
	 * @param newSalary  the new salary.
	 */
	public void setSalary(double newSalary) {

		salary = newSalary;
	}

	/*
	 public String toString() {
	 
	 return super.toString()+"  | salary:   "+salary;
	 }	*/
	
	public String toString() {

		return "name:   " + name + "  | address:  " + address
				+ "  | salary:   " + salary;
	}

/*
	public String toString() {

		return "name:   " + getName() + "  | address:  " + getAddress()
				+ "  | salary:   " + salary;
	}
*/
	public static void main(String[] arg) {
		Employee employee = new Employee("xiao", "nwpu", 200);
		System.out.println("name:" + employee.getName() + " address:"
				+ employee.getAddress() + " salary:" + employee.getSalary());
		
		Person person = new Employee("xiao", "nwpu", 200);
		System.out.println("name:" + person.getName() + " address:"
				+ person.getAddress() + " salary:" + person.getSalary());

		//System.out.println(employee);
	}
}
