/*!Begin Snippet:file*/
import  java.io.*;

/**
 * Makes a copy of a file.
 *
 * @author  author name
 * @version  1.0
 */
public class CopyFile  {

	/* Standard input stream */
	private static BufferedReader  stdIn =
			new BufferedReader(new  InputStreamReader(System.in));

	/* Standard output stream */
	private static PrintWriter  stdOut =
			new PrintWriter(System.out, true);

 	/* Standard error stream */
	private static PrintWriter  stdErr =
			new PrintWriter(System.err, true);

	/**
	 * Makes a copy of a file.
	 *
	 * @param args  not  used.
	 * @throws IOException  If an I/O error occurs.
	 */
	public static void  main(String[]  args) throws IOException  {

		stdErr.print("Source filename:  ");
		stdErr.flush();

		BufferedReader  input =
				new BufferedReader( 
						new FileReader(stdIn.readLine()));
         //"c://test/IOByteStream.java"
		//stdIn.readLine()
		stdErr.print("Destination filename:  ");
		stdErr.flush();

		PrintWriter  output =
				new  PrintWriter(new FileWriter(stdIn.readLine()));
        //stdIn.readLine()
		//"c://test/a.java"
		String  line = input.readLine();

		while (line != null)  {
			output.println(line);
			line = input.readLine();
		}

		input.close();
		output.close();

		stdOut.println("done");
	}
}
/*!End Snippet:file*/