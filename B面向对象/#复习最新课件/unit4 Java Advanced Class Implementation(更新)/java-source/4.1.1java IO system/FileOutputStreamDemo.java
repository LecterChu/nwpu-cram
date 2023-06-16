//FileOutputStreamDemo.java
import java.io.*;
public class FileOutputStreamDemo {
	
	
	private static final String NEW_LINE = 
				System.getProperty("line.separator");
	
	public static void main(String[] args) throws IOException {
	
		FileOutputStream writeFile = new FileOutputStream("out.txt");
		//FileWriter writeFile = new FileWriter("out.txt");
		String s = "happy new year!happy everyday!" 
				+"\n"+"wish fulfillment!"
				+"\n"+"ÄãºÃ\nEnd of file stream\n";
		
		for (int i = 0;i<s.length();i++){
		
			writeFile.write(s.charAt(i));
		}
		
		/*
		byte[] bytes = s.getBytes(); 
		writeFile.write(bytes);
		//writeFile.write(bytes,0,s.length());	*/		
		writeFile.close();		
	}
}