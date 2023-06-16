// Containers print themselves automatically.
import java.util.*;

public class PrintingContainers {
	
  static Collection<String> fill(Collection<String> c) {
  	
    c.add("dog");
    c.add("dog");
    c.add("cat");
    return c;
  }
  static Map<String,String> fill(Map<String,String> m) {
  	
    m.put("001", "Bosco");
    m.put("002", "Spot");
    m.put("003", "Rags");
    return m;
  }
  public static void main(String[] args) {
    System.out.println("Vector:  ");
    System.out.println(fill(new Vector<String>()));
    
    System.out.println("\nArrayList  :");	
    System.out.println(fill(new ArrayList<String>()));
    
    System.out.println("\nHashSet  :");
    System.out.println(fill(new HashSet<String>()));
    
    System.out.println("\nHashMap  :");
    System.out.println(fill(new HashMap<String,String>()));
   
    HashMap<String,String> hashMap = new HashMap<String,String>();
    fill(hashMap);
    
    System.out.println("\nkeyset:  ");
    System.out.println(hashMap.keySet());
    
    System.out.println("\nvalues:  ");
    System.out.println(hashMap.values());
    
    System.out.println("\nentrySet:  ");
    System.out.println(hashMap.entrySet());
    /**/
  }
} ///:~