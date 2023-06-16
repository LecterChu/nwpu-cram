import java.io.*;

/**
 * 计算一个数字的平方根
 */ 
public class SquareRoot {
	
	private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdOut =
        new PrintWriter(System.out, true);

    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);
    
    public static void computeSquRoot(){
    	try {
			stdErr.print("Enter an integer >  ");
	        stdErr.flush();
	        
	        String nStr = stdIn.readLine();       
			if (nStr == null){
				// 用throw关键字抛出异常，当异常被抛出时，程序会跳出该方法
				throw new EmptyException("输入的字符串不能为空！");
			}
			
			double n = 0;			
			n = Double.parseDouble(nStr);
			
			if (n < 0){
				throw new OutOfRangeException("输入的字符串转化成的数字必须大于等于0！");
			}
			
			stdOut.println("the square root of "+ nStr + " is:"+Math.sqrt(n));
			
		} catch(IOException e){			
			e.printStackTrace();
			
		} catch(EmptyException e){
			e.printStackTrace();
			
		} catch (NumberFormatException e){				
			e.printStackTrace();
			
		} catch(OutOfRangeException e){
			e.printStackTrace();			
		} 			
		stdOut.println("finish!");
    }
	
	public static void main(String[] args){
			
		SquareRoot.computeSquRoot();
	}
}
