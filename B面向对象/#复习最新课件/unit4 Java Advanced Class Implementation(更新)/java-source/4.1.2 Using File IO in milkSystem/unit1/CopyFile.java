/*!Begin Snippet:file*/
import  java.io.*;

/**
 * Makes a copy of a file.
 *
 * @author  author name
 * @version  1.0
 */
public class CopyFile  {
	private static BufferedReader  stdIn =
			new BufferedReader(new  InputStreamReader(System.in));
	private static PrintWriter  stdOut =
			new PrintWriter(System.out, true);
	private static PrintWriter  stdErr =
			new PrintWriter(System.err, true);

	public static void  main(String[]  args) throws IOException  {
		stdErr.print("Source filename:  ");
		stdErr.flush();
		BufferedReader  input =new BufferedReader( new FileReader(stdIn.readLine()));
		stdErr.print("Destination filename:  ");
		stdErr.flush();
		PrintWriter  output =new  PrintWriter(new FileWriter(stdIn.readLine()));
		String  line = input.readLine();
		while (line != null)  {
			output.println(line);
			line = input.readLine();
		}
		input.close();
		output.close();
	}
}
