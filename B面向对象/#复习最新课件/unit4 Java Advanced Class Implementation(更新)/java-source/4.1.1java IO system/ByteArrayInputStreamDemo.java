//ByteArrayInputStreamDemo.java
import java.io.*;

public class ByteArrayInputStreamDemo {
	
	private static final String NEW_LINE = 
				System.getProperty("line.separator");
	
	public static void main(String[] args) throws IOException {
		
	
		String s = "happy new year!happy everyday!" 
				+NEW_LINE+"wish fulfillment!ÄãºÃ"+NEW_LINE;
		byte[] bytes = s.getBytes();
				
		ByteArrayInputStream in1 = new ByteArrayInputStream(bytes);
		/* */      
		int intTemp = in1.read();
		while(intTemp!=-1){	
			System.out.println(intTemp);
			//System.out.println(" = "+(char)intTemp);
			intTemp = in1.read();
		 }
		in1.close();
		System.err.println("End of byte stream");
		 
		/*	
		byte[] buffer = new byte[2048];
		int byteLength = in1.read(buffer,0,2048);
		
		String str = new String(buffer,0,byteLength);
		System.out.println(str);
		
		in1.close();
		System.err.println("End of byte stream");
		*/ 	
		
	}
}























