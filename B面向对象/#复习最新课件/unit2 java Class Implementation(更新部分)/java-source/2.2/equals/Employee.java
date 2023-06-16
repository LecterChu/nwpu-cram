package equals;
/*!Begin Snippet:file*/
/**
 * This class models an Employee.
 *
 * @author author name
 * @version 1.0.0
 */
public class Employee extends Person  {

	/* Salary of the employee */
	private double salary;

	/**
	 * Constructs an <code>Employee</code> object.
	 *
	 * @param initialName  the name of the employee.
	 * @param initialAddress  the address of the employee.
	 * @param initialSalary  the salary of the employee.
	 */
	public Employee (String initialName, String initialAddress,
		double initialSalary) {

		 super(initialName, initialAddress);
		 salary = initialSalary;
	}

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
	public boolean equals(Object o) {
		
		
		
	}
	
	
	
	
     }
	
	
	public static void main(String[] arg){
		
		Employee employee1 = new Employee("xiao","nwpu",200);
		
		Employee employee2 = new Employee("xiao","nwpu",200);
		
		Employee employee3 = employee1;
		
		Person person = employee1;
		
		
		if (employee2.equals(employee1)) {
		     System.out.println("true");	
		} else {
		     System.out.println("false");
		}
		
		if (employee1 == employee3) {
		     System.out.println("true");	
		} else {
		     System.out.println("false");
		}
		/*		
		Person person = employee2; 
		//Person Person = new Person("xiao","nwpu");
		if (employee1.equals(person)) {
		     System.out.println("true");	
		} else {
		     System.out.println("false");
		}
		*/		
	}
}
/*!End Snippet:file*/
