// Typical I/O stream configurations.
import java.io.*;

public class IOStreamDemo {
	
	// Throw exceptions to console:
	public static void main(String[] args)throws IOException {
		
		try {
			// 1.Reading standard input by lines:			
			BufferedReader stdin =
			  new BufferedReader(
			    new InputStreamReader(System.in)); 
			         
			System.out.print("Enter a line:");
			System.out.println(stdin.readLine());
			
			// 2.Reading file input by lines:
			BufferedReader in1 =
			  new BufferedReader(
			     new FileReader(args[0]));
			     
			String s, s2 = new String();
			while((s = in1.readLine())!= null)
			  s2 += s + "\n";
			in1.close();
			
			// 3.Input from memory & BfferedWriter			
			BufferedReader in3 = new BufferedReader(
			     			new StringReader(s2));
			
			BufferedWriter out1 = new BufferedWriter(
			        		 new FileWriter("IODemo1.out"));
			int lineCount2 = 1;
			
			while((s = in3.readLine()) != null ){
				String s1 = lineCount2++ + ": " + s+"\r\n";
				out1.write(s1,0,s1.length());
			}
			
			in3.close();		
			out1.close();
			//////////////////////////////////////////////
			
			//  4. File output				
			
			BufferedReader in4 = new BufferedReader(
			     			new StringReader(s2));
			     			
			//PrintWriter out2 = new PrintWriter(
			//      		      new BufferedWriter(
			//        		 		new FileWriter("IODemo1.out")));
			PrintWriter out2 = new PrintWriter(
			      		      		new FileWriter("IODemo2.out"));
			int lineCount1 = 1;
			
			while((s = in4.readLine()) != null ){
				out2.println(lineCount1++ + ": " + s);
			}
						
			in4.close();
			out2.close();			
			///////////////////////////////////////////
			
		} catch(EOFException e) {				
			
			System.err.println("End of stream");	
				
		} catch(FileNotFoundException e) {
			
			System.err.println("File " + args[0] +" Not Found");
		}		
	}
} ///:~







