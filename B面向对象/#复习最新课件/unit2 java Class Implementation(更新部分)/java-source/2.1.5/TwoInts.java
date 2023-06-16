/*!Begin Snippet:file*/
/**
 * <p>This class store the value of two integers.</p>
 * <p>This class is written for the purpose of demonstrating Javadoc
 * comments. Javadoc comments for classes can be broken into two
 * parts: a description part and a tags part.  This is the
 * description part.  The parts should be separated by one empty
 * comment line.</p>
 * <p>Also, there should be no lines between the end of the Javadoc
 * comment and the beginning of the entity it describes.</p>
 *
 * @author  Lily Hou
 * @author  Sean Bufano
 * @version  1.0.0
 */
public class TwoInts  {

    private int  first;
    private int  second;

    /**
     * Initializes both integers to <code>0</code>.
     */
    public  TwoInts()  {

        first = 0;
        second = 0;
    }

    /**
     * Initializes both integers to arguments.
     *
     * @param initialFirst  value to which field <code>first</code>
     *                    is initialized
     * @param initialSecond  value to which field <code>second</code>
     *                     is initialized
     */
    public  TwoInts(int  initialFirst, int  initialSecond)  {

        first = initialFirst;
        second = initialSecond;
    }

    /**
     * Computes the sum of the two integers.
     *
     * @return  the sum of the two integers
     */
    public int  sum()  {

        return  first + second;
    }

    /**
     * Increments the field <code>first</code> by the argument.
     *
     * @param value  the value by which field <code>first</code> will
     *               be incremented
     */
    public void  addToFirst(int  value)  {

        first += value;
    }
}
/*!End Snippet:file*/
