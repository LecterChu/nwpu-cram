// Typical I/O stream configurations.

import java.io.*;
public class IOByteStream {
	
	private static final String NEW_LINE = System.getProperty("line.separator");
	
	public static void main(String[] args) throws IOException {
	
		//Formatted memory input
		try {
			String s = "I am studying inputStream and outputStream" 
				+NEW_LINE+"sucessful!"+NEW_LINE;
				
			DataInputStream in1 = new DataInputStream(
		          new ByteArrayInputStream(s.getBytes()));
		          
		    	while(true){
		    		System.out.print((char)in1.readByte());
		    	} 
		} catch(EOFException e) {
		  	System.err.println("End of stream");
		}
		
		// Storing & recovering data		
		try {
			DataOutputStream out1 =
		          new DataOutputStream(
		            new BufferedOutputStream(
		              new FileOutputStream("Data.txt")));
		              
		        out1.writeDouble(3.14159);
		        out1.writeChars("That was pi\n");
		        out1.writeBytes("That was pi\n");
		        out1.close();
		        
		        
		        DataInputStream in2 =
		          new DataInputStream(
		            new BufferedInputStream(
		              new FileInputStream("Data.txt")));
		       
			// Must use DataInputStream for data:
			System.out.println(in2.readDouble());
			
			char c = in2.readChar();
			
			while(c != '\n') {
				
				System.out.print(c);
				c = in2.readChar();
			}			
			System.out.println(c);
			
			byte b = in2.readByte();
			
			while((char)(b) != '\n') {
				
				System.out.print((char)(b));
				b = in2.readByte();
			}		
			System.out.println((char)(b));
			in2.readByte();
			
		} catch(EOFException e) {
			System.err.println("End of stream");
		}
	}
}