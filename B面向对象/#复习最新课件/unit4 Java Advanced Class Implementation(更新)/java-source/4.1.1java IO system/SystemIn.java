import java.io.*;

public class SystemIn {

	public static void main(String[] args) throws IOException{
		
		int in = System.in.read();
		
		while((char)in!='\n') {
			
			System.out.print((char)in);
			in = System.in.read();
		}	
	}
}