

public class SprinklerSystem {
	
	private String valve1 = new String("valvel"),
		       valve2 = new String("valve2");
	
	WaterSource source = new WaterSource();
	
	int i = 0;	
	
	void print() {
		
	  System.out.println("valve1 = " + valve1);
	  System.out.println("valve2 = " + valve2);	 
	  System.out.println("source = " + source);
	}	
	
	public static void main(String[] args) {
		
	  SprinklerSystem x = new SprinklerSystem();
	  x.print();	
	  WaterSource.main(null); 	   
	}
} ///:~

class WaterSource {
	
	private String s;
		
	WaterSource() {
		
	  System.out.println("WaterSource():Constructed");
	  s = new String("WaterSource");
	}
	
	public String toString() { return s; }
	
	public static void main(String args[]) {
		
		System.out.println("the main method of WaterSource");
	
	}
}
	

