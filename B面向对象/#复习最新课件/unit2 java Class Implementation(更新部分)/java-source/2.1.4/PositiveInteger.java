/*!Begin Snippet:file*/
import java.io.*;

/**
 * Wraps a positive integer value.
 *
 * @author author name
 * @version 1.0.0
 */
public class PositiveInteger  {

    private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);

    private static PrintWriter  stdOut =
        new PrintWriter(System.err, true);

    private int value;

    /**
     * Tests method <code>readInteger</code>
     *
     * @param args  not used
     * @throws IOException if error reading from standard input.
     */
    public static void  main(String[] args) throws IOException  {

        PositiveInteger object;

        do  {
            try  {
                stdErr.print("Enter an integer> ");
                stdErr.flush();

                int value = Integer.parseInt(stdIn.readLine());
                object = new  PositiveInteger(value);

                break;

            } catch (NumberFormatException  nfe)  {
                stdErr.println("Invalid number format");
            } catch (OutOfRangeException  ore)  {
                stdErr.println(ore.getMessage());
            }
        }  while (true);

        stdOut.println("The value is: " + object.getValue());
    }

    /**
     * Constructs a <code>PositiveInteger</code> object with the
     * value specified by the argument.
     *
     * @param initialValue  an integer. The value should be positive.
     * @throws OutOfRangeException  if the value is negative.
     */
    private PositiveInteger(int initialValue) throws OutOfRangeException {

        if (initialValue < 0) {

            throw new OutOfRangeException("Number not positive");

        } else {
            value = initialValue;
        }
    }

    /**
     * Returns the positive number
     *
     * @return the value
     */
    public int getValue()  {

        return value;
    }

    /**
     * Modify the positive number.
     *
     * @param newValue  the new integer. The value should be positive.
     * @throws OutOfRangeException  if the new value is negative.
     */
    private void setValue (int newValue) throws OutOfRangeException {

        if (newValue < 0) {

            throw new OutOfRangeException("Number not positive");

        } else {
            value = newValue;
        }
    }
}
/*!End Snippet:file*/
