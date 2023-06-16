/*!Begin Snippet:file*/
import  java.io.*;

public class Hello  {

    private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdOut =
        new PrintWriter(System.out, true);
   
    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);
        
    public static void  main(String[]  args) throws IOException {

        stdErr.print("Please enter you name on this line:  ");
        stdErr.flush();
        
        String  input = stdIn.readLine();
        
        stdOut.println("Hello " + input);
    }
}
/*!End Snippet:file*/
