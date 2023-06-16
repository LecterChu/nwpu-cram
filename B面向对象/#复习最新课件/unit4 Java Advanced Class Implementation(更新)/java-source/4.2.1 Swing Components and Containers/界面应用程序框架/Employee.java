import java.util.*;

/**
 * @author Administrator
 *
 */
public class Employee
{
	private String name;
	private float salary;
	private Vector<Employee> subordinates;
	
	/**
	 * @param initialName
	 * @param initialSalary
	 */
	public Employee(String initialName, float initialSalary) {
		
		name = initialName;
		salary = initialSalary;
		subordinates = new Vector();
	}
	
	/**
	 * @return
	 */
	public float getSalary() {
		
		return salary;
	}
	
	/**
	 * @return
	 */
	public String getName() {
		
		return name;
	}
	/**
	 * @param e
	 */
	public void add(Employee e) {
		
		subordinates.add(e);
	}
	
	/**
	 * @param e
	 */
	public void remove(Employee e) {
		
		subordinates.remove(e);
	}
	
	/**
	 * @return
	 */
	public Iterator<Employee> iterator() {
		
		return subordinates.iterator();
	}
	
	/**
	 * @return
	 */
	public float getSalaries() {
		
		float sum = salary;
		
		for(Employee e :subordinates) {
			
			sum += e.getSalaries();
		}
		return sum;
	}
	
	/**
	 * @param str
	 * @return
	 */
	public Employee getChild(String str) {

		if (str.equals(getName())) {

			return this;

		} else {

			for (Employee e : subordinates) {

				if (e.getName().equals(str)) {

					return e;
				}

				if (e.getChild(str) != null) {

					return e.getChild(str);
				}
			}
			return null;

		}
	}
}