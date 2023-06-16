

public class ValuePassing {

	public static void main(String[] args) {      
		Point2D point1=new Point2D(100,200);
		
		System.out.println("before chaning:");
		System.out.println("str1是:"+point1);
		change(point1);
		System.out.println("after chaning:");
		System.out.println("str1是:"+point1);
		
    }
	public static void change(Point2D p1) {  
		float x=3333;
		p1.setX(x);
		p1=  new Point2D(7777,8888);

		
	}
	
//	public static void main(String[] args) {      
//		StringBuilder str1=new StringBuilder("AAA");
//		StringBuilder str2=new StringBuilder("BBB");
//		StringBuilder str3=new StringBuilder("CCC");
//		System.out.println("before chaning:");
//		System.out.println("str1是:"+str1);
//		System.out.println("str2是:"+str2);
//		System.out.println("str3是:"+str3);
//		change(str1,str2,str3);
//		System.out.println("after chaning:");
//		System.out.println("str1是:"+str1);
//		System.out.println("str2是:"+str2);
//		System.out.println("str3是:"+str3);
//    }
//	public static void change(StringBuilder str1,StringBuilder str2,StringBuilder str3) {  
//		str3=str1;
//		str1=str2;
//		str2=str3;
//		//str1.append("1");
//		//str2.append("2");
//	}



}
	

