import  java.io.*;

/**
 * This class demonstrates the use of the container classes.
 *
 * @author author mcy
 * @version 1.0.0
 * @see Person
 * @see Client
 * @see Employee
 */
public class PersonDemo {

	private static PrintWriter  stdOut =
		new PrintWriter(System.out, true);
		
	private  static String[] names = {
		"Chocolate", "Strawberry",
		"Vanilla Fudge Swirl", "Mint Chip",
		"Mocha Almond Fudge", "Rum Raisin",
		"Praline Cream", "Mud Pie" };
		
	public static Person randPerson() {
		
		int index = (int)(Math.random() * 7);
		int age= (int)(Math.random() * 100);
		double salary = Math.random() * 300; 
		
		switch((int)(Math.random() * 3)) {
			default:			
			case 0: return new Employee(PersonDemo.names[index],age);
			case 1: return new Client(PersonDemo.names[index],salary);
			case 2: return new Person(PersonDemo.names[index]);
	  	}
	}	
	 
	/**
	 * Demonstrates the use of polymorphism in the container
	 * classes.
	 *
	 * @param args  not used.
	 */
	public static void  main(String[]  args) {

		Person[] person = new Person[8];
		
		for (int index=0; index<8; index++){
			person[index] = PersonDemo.randPerson();
		}
		
		for (int index=0; index<8; index++){
			stdOut.println(person[index]);
		}
		
	}
}