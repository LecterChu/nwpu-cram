/*!Begin Snippet:file*/
/**
 * This class demonstrates exception throwing and catching.
 *
 * @author author name
 * @version 1.0.0
 */
public class ExceptionDemo {

    /**
     * Calls methodA
     *
     * @param args  not used
     */
    public static void  main(String[] args)  {

        methodA();
        System.out.println("MethodA passed");
    }

    /**
     * Calls methodB. If an exception occurs; catches it, reports the
     * error, and terminate the program.
     */
    public static void  methodA()  {

        try {
            methodB();
            System.out.println("MethodB passed");
        } catch (Exception e) {
            e.printStackTrace();

            System.exit(1);
        }
    }

    /**
     * Calls methodC. If an exception occurs, throws it to the calling
     * method.
     *
     * @throws Exception  when methodC is called.
     */
    public static void  methodB() throws  Exception  {

        methodC();
        System.out.println("MethodC passed");
    }

     /**
     * Throws an exception
     *
     * @throws Exception  whenever methodD is called.
     */
    public static void  methodC() throws  Exception  {

        throw new  Exception("This is an Exception Message");
    }
}
/*!End Snippet:file*/
