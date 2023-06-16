import  java.util.*;  

public class StringClassDemo  {
                

                 public static int getNumberOfA(String str){
                   
                             //返回字符串str中小写的a的个数
                 return 0;
                }
	public static void  main(String[]  args)  {

		String  strHello = new  String("Hello");	
                     	
		System.out.println(getNumberOfA(strHello));


		String  strWorld = "World";		
				
		strWorld = new  String("I love writing Java  program");

		System.out.println(getNumberOfA(strWorld ));
		
		if (strHello == strWorld)  {
			System.out.println("The strings are equivalent according to ==");
		} else {
			System.out.println("The strings are not equivalent according to ==");
		}
		strWorld = "World";	
		
		if (strHello.length() != strWorld.length())  {
			System.out.println("not ");
		} else {
			System.out.println("equal in length");
		}
		/*	
		//类String的equals( )方法比较的是字符串的内容是否相等		
		if (strHello.equals(strWorld))  {
			System.out.println("The strings are equivalent according to the method equals()");
		}
		*/
		// the == compares the addresses of the objects
		/**/
		System.out.println(strWorld.charAt(2));
		System.out.println(strHello.indexOf('l'));
		System.out.println(strWorld.indexOf("or"));	
		System.out.println((strHello + strWorld).indexOf('o', 5));
		
		String  strValues;	
		strValues = String.valueOf(5.87);  // strValues is now "5.87"
		strValues = String.valueOf(true);  // strValues is now "true"
		strValues = String.valueOf(18);  // strValues is now "18"
		// 字符串连接
		System.out.println(5.87 + " " + true + " " + 18);  // prints 5.87true18
		System.out.println(5.87 + 18 +" "+ true  );		
		
		System.out.println(strHello + "\t" + strWorld  + "\t" );
		System.out.println(strHello + "\\" + strWorld  + "\\" );
		System.out.println("\"" + strHello + "\" and \"" + strWorld + "\"");
	}
}