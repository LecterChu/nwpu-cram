//FileInputStreamDemo.java
import java.io.*;
public class FileInputStreamDemo {
	
	
	private static final String NEW_LINE = 
				System.getProperty("line.separator");
	
	public static void main(String[] args) throws IOException {
		
         FileReader readFile = new FileReader("FileInputStreamDemo.java");
		int intTemp = readFile.read();
		while(intTemp!=-1){
			System.out.print((char)intTemp);
			intTemp = readFile.read();
		 }		
		readFile.close();
		
	}
}






















