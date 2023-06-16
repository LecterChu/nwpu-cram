/*!Begin Snippet:file*/
import java.io.*;

/**
 * This class provides a method that reads an integer from the
 * standard input.
 *
 * @author author name
 * @version 1.0.0
 */
public class IntegerReaderThrowsException  {

    private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);

    private static PrintWriter  stdOut =
        new PrintWriter(System.err, true);

    /**
     * Tests method <code>readInteger</code>
     *
     * @param args  not used
     * @throws IOException if error reading from standard input.
     */
    public static void main (String[] args) throws IOException {

        stdOut.println("The value is: " + readInteger());
    }

    /**
     * Reads an integer from the standard output.
     *
     * @return the <code>int</code> value.
     * @throws IOException if error reading from standard input.
     */
    public static int  readInteger() throws IOException {

        do  {
            try  {
                stdErr.print("Enter an integer> ");
                stdErr.flush();

                return Integer.parseInt(stdIn.readLine());

            } catch (NumberFormatException  nfe)  {
                stdErr.println("Invalid number format");
            }
        }  while (true);
    }
}
/*!End Snippet:file*/
