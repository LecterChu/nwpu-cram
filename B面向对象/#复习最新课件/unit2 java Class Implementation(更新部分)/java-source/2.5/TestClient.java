
import  java.util.*;
import  java.io.*;

/**
 * This class tests the implementation of class <code>Client</code>.
 *
  
 */
public class TestClient  {

	/* Standard output stream */
	private static PrintWriter  stdOut =
		new  PrintWriter(System.out, true);

	/* Standard error stream */
	private static PrintWriter  stdErr =
		new  PrintWriter(System.err, true);

	/**
	 * Tests the implementation of class <code>Client</code>.
	 *
	 * @param args  not used.
	 */
	public static void main(String[] args) {

		BankAccount accountOne = new BankAccount();
		BankAccount accountTwo = new BankAccount();
		BankAccount accountThree = new BankAccount();

		accountOne.deposit(1000.0);
		accountTwo.deposit(2000.0);
		accountThree.deposit(3000.0);
		
		Client client= new Client("John Smith");

		client.addAccount(accountOne);
		client.addAccount(accountTwo);
		client.addAccount(accountThree);

		double totalBalance = 0.0;
		
		for (BankAccount account : client) {
			totalBalance += account.getBalance();
		}
		
		if (totalBalance != 6000.0) {
			stdErr.println("** Test failure");
		}
		
		stdOut.println("done");
	}
}

/*!End Snippet:file*/