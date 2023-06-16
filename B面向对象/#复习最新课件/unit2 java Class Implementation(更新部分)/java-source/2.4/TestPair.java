/*
class Pair <A,B> {

	  private A element1;
	  private B element2;
	  
	  public Pair(A element1, B element2){
	  
	      this.element1 = element1;
	      this.element2 = element2; 
	  }
	     
	  public A getElement1(){
	  
	      return element1;
	  }
	  
	  public B getElement2(){
	  
	      return element2;
	  }
  
}

public class TestPair {
	
	public static void main(String[] args) {

		Pair<String,String> pairOne  = new Pair<String,String>("1","2");
		System.out.println(pairOne.getElement1()+" "+ pairOne.getElement2());
		
		Pair<Point2D,Point2D> pairTwo  = new Pair<Point2D,Point2D>(new Point2D(100,200),new Point2D(300,400));
		System.out.println(pairTwo.getElement1()+" "+ pairTwo.getElement2());
		
		Pair<Point2D,String> pairThree  = new Pair<Point2D,String>(new Point2D(100,200),"2");
		System.out.println(pairThree.getElement1()+" "+ pairThree.getElement2());
	}
} 

*/
class Pair {
	
	  private String element1;
	  private String element2;
	  
	  public Pair(String element1,String element2){
		  
	      this.element1 = element1;
	      this.element2 = element2; 
	  }
	    
	  public String getElement1(){
		  
	      return element1;
	  }
	  
	  public String getElement2(){
		  
	      return element2;
	  }
	  public static void main(String[] args) {

			Pair pairOne  = new Pair("1","2");
			System.out.println(pairOne.getElement1()+" "+ pairOne.getElement2());
			
	  }
}

