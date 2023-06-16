/*!Begin Snippet:file*/
import java.io.*;

/**
 * This class provides a method that reads an integer from the
 * standard input.
 *
 * @author author name
 * @version 1.0.0
 */
public class IntegerReader  {

    private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);

    private static PrintWriter  stdOut =
        new PrintWriter(System.out, true);

    /**
     * Tests the method <code>readInteger</code>.
     *
     * @param args  not used.
     */
    public static void main (String[] args) {

        stdOut.println("The value is: " + readInteger());
    }

    /**
     * Reads an integer from the standard output.
     *
     * @return the <code>int</code> value.
     */
    public static int  readInteger()  {//throws IOException

        do  {
            try  {
                stdErr.print("Enter an integer >  ");
                stdErr.flush();
               
                return Integer.parseInt(stdIn.readLine());
                

            } catch (NumberFormatException  nfe)  {
            	
                stdErr.println("Invalid number format");
            } catch (IOException  ioe)  {
                ioe.printStackTrace();

               // System.exit(1);     // Terminates the program

            } //catch(Exception ioe) {
            //} 
           /* finally {
            	stdOut.println("--------------");
            }
           // stdOut.println("running after catch");
           // stdOut.println("--------------");
            */
        }  while (true);
    }
}
/*!End Snippet:file*/
