/*!Begin Snippet:file*/
import  java.io.*;

/**
 * This class demonstrates the use of class {@link ICarnegieInfo}.
 *
 * @author author name
 * @version  1.0.0
 * @see  ICarnegieInfo
 */
public class ICarnegieInfoDemo  {
	
	private static PrintWriter  stdOut =
		new  PrintWriter(System.out, true);

	/**
	 * Demonstrate the use of class {@link ICarnegieInfo}.
	 *
	 * @param args  not used
	 */
	public static void main(String[]  args)  {

		ICarnegieInfo companyInfo = ICarnegieInfo.getSingletonInstance();

		stdOut.println("Name:      " + companyInfo.getName());
		stdOut.println("Address:   " + companyInfo.getAddress());
		stdOut.println("Telephone: " + companyInfo.getTelephone());
	}
}
