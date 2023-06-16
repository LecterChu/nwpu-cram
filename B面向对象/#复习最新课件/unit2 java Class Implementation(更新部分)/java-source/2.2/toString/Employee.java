package toString;
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
        if (o instanceof Employee) {
        	
        	Employee e = (Employee)o;
        	return this.getName().equals(e.getName()) 
        	       && this.getAddress().equals(e.getAddress())
        	       && this.getSalary() == e.getSalary() ;
        }else {
        	
        	return false;          
        } 
	}
	/*
	public String toString() {
		
		return super.toString()+"  | salary:   "+salary;
	}	
	*/
	
	public static void main(String[] arg){
		
		Employee employee = new Employee("xiao","nwpu",200);
		Person person = employee;		
		
		System.out.println(employee.getName());
		System.out.println(employee.getAddress());
		System.out.println(employee.getSalary());
		System.out.println(employee);
		
	}
}
/*!End Snippet:file*/
