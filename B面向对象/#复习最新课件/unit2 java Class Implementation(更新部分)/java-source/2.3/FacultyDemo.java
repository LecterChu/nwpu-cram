import java.io.*;

public class FacultyDemo {

	private static PrintWriter  stdOut =
		new PrintWriter(System.out, true);
	
	private static String[] ids = {
	   "A001","A002","A003","B001",
	   "B002","B003", "C001","C002",
	   "C003"
	};
	private static String[] teles = {
		"13791282722","13491282722","13951282722",
		"13991252722",
		"13341282722","123991282762","13771282722",
		"13991282799","13991432722"
	};
		
	private  static String[] names = {
		"Chocolate", "Strawberry",
		"Vanilla Fudge Swirl", "Mint Chip",
		"Mocha Almond Fudge", "Rum Raisin",
		"Praline Cream", "Mud Pie","apple" };
	private static String[] titles = {
		"professor", "viceProfessor","lecture"};
	private static String[] jobPositions = {
		
		"Job1","Job2","Job3"
	};
	private static String[] degrees = {
		
		"undergraduate","master","doctor"
	};
	
	public static FacultyMember randMember() {
		
		int index1 = (int)(Math.random() * 9);
		int index2= (int)(Math.random() * 3);		
		
		switch((int)(Math.random() * 4)) {
			default:
			case 0: return new Teacher(ids[index1],names[index1],
					                   teles[index1],titles[index2]);
			case 1: return new Official(ids[index1],names[index1],
	                   teles[index1],jobPositions[index2]);
			case 2: return new Experimenter(ids[index1],names[index1],
	                   teles[index1],degrees[index2]);
			case 3: return new FacultyMember(ids[index1],names[index1],
	                   teles[index1]);
	  	}
	}	
	 
	/**
	 * Demonstrates the use of polymorphism in the container
	 * classes.
	 *
	 * @param args  not used.
	 */
	public static void  main(String[]  args) {

		FacultyMember[] members = new FacultyMember[35];
		
		for (int index=0; index<members.length; index++){
			members[index] = randMember();
		}
		
		for (int index=0; index<members.length; index++){
			stdOut.println(members[index].toString());
		}
		
	}
}
