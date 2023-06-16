/*
 * BankAccount.h
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_
 class BankAccount {

	/* Balance of the account*/
 private:
	double balance;
  public:
	  BankAccount(double balance=0);
	  double getBalance();
	  bool deposit(double amount);
      bool withdraw(double amount);
 };
#endif /* BANKACCOUNT_H_ */
