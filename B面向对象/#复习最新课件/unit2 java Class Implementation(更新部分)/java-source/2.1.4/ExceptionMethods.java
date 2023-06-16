//ExceptionMethods.java
//Demonstrating the  exception methods
public class ExceptionMethods {
	
	public static void f() throws Exception {
		
		throw new Exception("This is my test Exception");		
	} 
	
	public static void g() throws Exception {
		
		f();		
		System.out.println("the code after f() call");
			
	}
	
	public static void main(String[] arg) {
		
		try {
			
			g();
			System.out.println("the code after g() call");
					
		} catch(Exception e) {
			
			System.out.println("e.getMessage():  "+e.getMessage());
			System.out.println("e.toString:  "+e.toString());
			System.out.println("e.printStackTrace:  ");
			e.printStackTrace();
		}
	}
}
