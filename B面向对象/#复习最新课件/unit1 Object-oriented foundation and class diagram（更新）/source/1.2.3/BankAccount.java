/*!Begin Snippet:file*/
/**
 * This class models a bank account.
 *
 * @author iCarnegie
 * @version 1.0.0
 */
public class BankAccount {

	/* Balance of the account*/
	private double balance;

	/**
	 * Creates a new <code>BankAccount</code> object with an
	 * initial balance of zero.
	 */
	public BankAccount() {

		this.balance = 0.0;
	}

	/**
	 * Returns the balance of this account.
	 *
	 * @return the balance of this account
	 */
	public double getBalance() {

		return this.balance;
	}

	/**
	 * Deposits money in this account. If the specified amount is
	 * positive, the account balance is updated.
	 *
	 * @param amount amount of money to add to the balance.
	 * @return <code>true</code> if the money is deposited;
	 *         <code>false</code> otherwise.
	 */
	public boolean deposit(double amount) {

		if (amount > 0) {
			this.balance += amount;

			return true;
		} else {

			return false;
		}
	}

	/**
	 * Withdraws money from this account. If the specified amount is
	 * positive and the account has sufficient funds, the
	 * account balance is updated.
	 *
	 * @param amount  amount of money to subtract from the balance.
	 * @return <code>true</code> if the money is withdrawn;
	 *         <code>false</code> otherwise.
	 */
	public boolean withdraw(double amount) {

		if (amount > 0 && this.balance >= amount) {
			this.balance -= amount;

			return true;
		} else {

			return false;
		}
	}
}
/*!End Snippet:file*/
