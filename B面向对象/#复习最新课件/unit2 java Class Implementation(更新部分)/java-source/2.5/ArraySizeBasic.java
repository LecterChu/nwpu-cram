
// Initialization & re-assignment of arrays.

public class ArraySizeBasic {
	
	public static void main(String[] args) {
		
        // Arrays of primitives:
		int[] e; // Null reference
		int[] f =  {11,47,93,33,44};
		int[] g = new int[4];
		    
		e = new int[] { 1, 2 };	
		
		for(int i = 0; i < g.length; i++){
			g[i] = i*i;
		} 
			    
		f = g;
				
		System.out.println("e.length = " + e.length);    
		System.out.println("f.length = " + f.length);
		System.out.println("g.length = " + g.length);		    
		
	}
}