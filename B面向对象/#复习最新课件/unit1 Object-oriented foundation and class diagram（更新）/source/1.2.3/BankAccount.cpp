/*
 * BankAccount.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */

   #include "BankAccount.h"


	BankAccount::BankAccount(double initialBalance) {

			balance = initialBalance;
		}

	double BankAccount::getBalance() {

		return balance;
	}

	bool BankAccount::deposit(double amount) {

		if (amount > 0) {
			balance += amount;

			return true;
		} else {

			return false;
		}
	}

	bool BankAccount::withdraw(double amount) {

		if (amount > 0 && this->balance >= amount) {
			balance -= amount;

			return true;
		} else {

			return false;
		}
	}


