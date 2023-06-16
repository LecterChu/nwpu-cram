
/*
A common Java interface that we use in our test
programs is Comparable. This interface requires that the class provides a method
int compareTo(Object o) {...}
*/
public class Comparison {
    
	/*Comparable is an interface requiring a class to have a
	method compareTo() that determines the order of objects of that class. Any time the
	method min() is called, it has to be on a class that implements Comparable.*/
	/*
	public Comparable min (Comparable a, Comparable b) {
		if (a.compareTo(b) < 0) return a;
		else return b;
	}
	
    */

	public static <K extends Comparable> K min(K k1, K k2) {
		if (k1.compareTo(k2) > 0) {
			return k2;
		} else { 
			return k1;
		}
	}
	public static void main(String[] args){
		
		int m =10, n=100;
		int i = min(n,m);
		float j =12.6f, k=21.9f;
		float f = min(j,k);
		System.out.println("the min value of m and n is "+ i+ "\n the min value of j and k is  " + f);
	  
	
	}
}