

class Weeble {} 

public class ArraySizeObject {
	
	public static void main(String[] args) {
		
			
		Weeble[] a = new Weeble[] {
			new Weeble(), new Weeble()
		};
		
		Weeble[] b = new Weeble[5]; 
		Weeble[] c = new Weeble[4];
		  
		for(int i = 0; i < c.length; i++){
			c[i] = new Weeble();
		}
		  		    
		Weeble[] d = { 
			new Weeble(), new Weeble(), new Weeble()
		};
		
		a = d;
		b = c;  
		
		for(int i = 0; i < b.length; i++){
			System.out.println("b[" + i + "]=" + b[i]); 	
		}		        
		    
		System.out.println("e.length = " + a.length);    
		System.out.println("f.length = " + b.length);
		System.out.println("g.length = " + c.length);	
		System.out.println("g.length = " + d.length);
		
	}
} ///:~