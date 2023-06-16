/**
*@author:ma chun yan
*@version:1.0.0
*/
import java.io.*;
import java.util.*;

public class PersonVector {
	
	private  final static String NEW_LINE =
	        System.getProperty("line.separator");
	
	private Vector people;
	
	public PersonVector() {
	
		people = new Vector();
	}
	
	public void addPerson(Person person) {
		
		people.add(person);
			
	}
	
	public Person getPerson(int index) {

		return (Person)people.get(index); 	
	} 
	
	public int  getNumberOfPerson()  {

		return people.size();
	}
	
	public String toString() {
		
		String out = "";		
		
		for (int i =0; i< people.size(); i++) {
			out = out + people.get(i) + NEW_LINE;			
		}
		
		return out;
	} 	
}