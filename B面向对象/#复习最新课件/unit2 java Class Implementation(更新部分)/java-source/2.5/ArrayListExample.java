/**
 * @author Administrator
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
import java.util.*;
public class ArrayListExample {
	
	public static void main(String args[]){
	    
		ArrayList<Person> people = new ArrayList<Person>();
	   	    	    
		people.add(new Person("xiao1","nwpu1"));
		people.add(new Person("xiao2","nwpu2"));
		people.add(new Person("xiao3","nwpu3"));
		// a.add(new Integer(4));		
		/*±éÀúÈÝÆ÷*/	 
		for(int j = 0; j < people.size(); j++){
			Person person = people.get(j);  
	            	System.out.println(person);                      
		} 		
		System.out.println("----------iterator---------"); 
		Iterator<Person> e = people.iterator();	    
		    while(e.hasNext()){		    	
		    	Person person = e.next();
		        System.out.println(person);
		    }		
		/*
		System.out.println("----------for each---------");     
		for (Person person:people) {		    
			System.out.println(person);
		} 
		*/
	    
	}
}
