/*
 * Client.h
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */

#ifndef CLIENT_H_
#define CLIENT_H_
#include <string>
#include <vector>
#include "BankAccount.h"
using namespace std;

class Client {

   private:
	     string name;
	     vector<BankAccount>  accounts;
	public:
		 Client(string initialName);
	     string  getName();
	     void  addAccount(BankAccount bankAccount);
	 	 vector<BankAccount> ::iterator  Client::iteratorBegin();
	 	 vector<BankAccount> ::iterator  Client::iteratorEnd();
	 	 vector<BankAccount>::size_type  getNumberOfAccounts();
	     BankAccount operator[](vector<BankAccount>::size_type index);

};

#endif /* CLIENT_H_ */
