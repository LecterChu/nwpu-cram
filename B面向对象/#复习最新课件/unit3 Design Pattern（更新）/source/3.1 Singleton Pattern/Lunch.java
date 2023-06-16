// Make a class effectively private
// with private constructors:

class Soup {
	
	private Soup() {}
	// (1) Allow creation via static method:
	public static Soup makeSoup() {
	  	
		return new Soup();
	}
	  // (2) Create a static object and
	  // return a reference upon request.
	  // (The "Singleton" pattern):
	private static Soup ps1 = new Soup();
	  
	public static Soup access() {
	  	
		return ps1;
	}
	  
	public void f() {}
}

class Sandwich { // Uses Lunch

	void f() { new Lunch(); }
}

// Only one public class allowed per file:
public class Lunch {
	
  void test() {
    // Can't do this! Private constructor:
    //! Soup priv1 = new Soup();
    Soup priv2 = Soup.makeSoup();
    Sandwich f1 = new Sandwich();
    Soup.access().f();
  }
} ///:~