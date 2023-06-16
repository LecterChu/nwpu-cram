/*!Begin Snippet:file*/
import  java.io.*;
import  java.util.*;

public class ReadThreeIntegers  {

    private static BufferedReader  stdIn =
        new BufferedReader(new  InputStreamReader(System.in));

    private static PrintWriter  stdOut =
        new PrintWriter(System.out, true);

    private static PrintWriter  stdErr =
        new PrintWriter(System.err, true);

    public static void  main(String[]  args) throws IOException {

        stdErr.print("Enter three integers on one line:  ");
        stdErr.flush();

        StringTokenizer  tokenizer =
            new  StringTokenizer(stdIn.readLine());

        if (tokenizer.countTokens() != 3) {
            stdErr.println("Invalid input");
        } else {

            int  firstValue = Integer.parseInt(tokenizer.nextToken());
            int  secondValue = Integer.parseInt(tokenizer.nextToken());
            int  thirdValue = Integer.parseInt(tokenizer.nextToken());
            int sum =firstValue + secondValue + thirdValue;
            stdOut.println("sum: " + sum);
            stdOut.println("sum: " + firstValue + secondValue
					+ thirdValue);
            
        }
    }
}
/*!End Snippet:file*/
