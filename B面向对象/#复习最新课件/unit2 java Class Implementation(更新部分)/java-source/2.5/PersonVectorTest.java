import java.io.*;

	public class PersonVectorTest {
	
	private  final static String NEW_LINE =
	        System.getProperty("line.separator");
	private  static String[] names = {
		"Chocolate", "Strawberry",
		"Vanilla Fudge Swirl", "Mint Chip",
		"Mocha Almond Fudge", "Rum Raisin",
		"Praline Cream", "Mud Pie" };
		
	private static String[] addresses = {
		"desk", "computer", "house", 
		"world", "book", "money", "river", 
		"paper"};
		
	private static PrintWriter  stdOut =
	    	new  PrintWriter(System.out, true);

	public static void main(String[] args) {
		
		String out = "" ;
		PersonVector personVector = new PersonVector();
		
		for (int i =0; i< 8; i++) {
			personVector.addPerson(new Person(names[i], addresses[i]));
		}	
		
		for (int i =0; i< personVector.getNumberOfPerson(); i++) {
			out = out + personVector.getPerson(i) + NEW_LINE;			
		}
		stdOut.println(out);
		
		stdOut.println(personVector);
	}

}
