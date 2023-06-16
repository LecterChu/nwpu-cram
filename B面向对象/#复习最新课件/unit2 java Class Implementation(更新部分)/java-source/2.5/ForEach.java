//: c09:Iterators2.java
// From 'Thinking in Java, 2nd ed.' by Bruce Eckel
// www.BruceEckel.com. See copyright notice in CopyRight.txt.
// Revisiting Iterators.
import java.util.*;

class PrintData {
	/**/
	static void print(Collection<Mouse> e) {
		
	 for(Mouse m :e) {
	    System.out.println(m);
	    
	 }
	}
	
	/*
	static void print(Collection<Mouse> e) {
		for(Mouse mouse:e) {
			 System.out.println(mouse);
		}
		  
	}
	*/
}

public class ForEach {
	
	public static void main(String[] args) {
		
		ArrayList<Mouse> arrayList = new ArrayList<Mouse>();
		
		for(int i = 0; i < 5; i++) {
			arrayList.add(new Mouse(i));
		}
		
		Vector<Mouse> v = new Vector<Mouse>();
		for(int i = 0; i < 5; i++) {
			v.add(new Mouse(i));
		}
		
		HashSet<Mouse> l = new HashSet<Mouse>();
		for(int i = 0; i < 5; i++) {
			l.add(new Mouse(i));
		}	    
		System.out.println("----------ArrayList------");		
		PrintData.print(arrayList);
		
		
		System.out.println("-----------Vector---------");		
		PrintData.print(v);	
		
		System.out.println("-----------HashSet---------");		
		PrintData.print(l);		
		
	}
} ///:~