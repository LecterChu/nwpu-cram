/*
 * Client.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */
	#include "Client.h"
    #include <string>
    using namespace std;

	Client::Client(string initialName) {

		this->name = initialName;
	 }
	string  Client::getName() {

		return this->name;
	}	

	void  Client::addAccount(BankAccount bankAccount)  {

		this->accounts.push_back(bankAccount);
	}

	vector<BankAccount>::iterator Client::iteratorBegin() {

		return this->accounts.begin();
	}
	vector<BankAccount>::iterator  Client::iteratorEnd() {

			return this->accounts.end();
	}

	vector<BankAccount>::size_type  Client::getNumberOfAccounts(){

		return this->accounts.size();
	}
	 BankAccount Client::operator[](vector<BankAccount>::size_type index){

           return accounts[index];
	 }



/*!End Snippet:file*/
