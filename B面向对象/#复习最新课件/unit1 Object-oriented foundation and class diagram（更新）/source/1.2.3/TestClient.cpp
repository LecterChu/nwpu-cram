/*
 * TestClient.cpp
 *
 *  Created on: 2013-10-25
 *      Author: Administrator
 */
    #include "BankAccount.h"
    #include "client.h"
    #include <iostream>
    #include <vector>
    using namespace std;

	int main() {
		BankAccount accountOne;
		BankAccount accountTwo;
		BankAccount accountThree;

		accountOne.deposit(1000.0);
		accountTwo.deposit(2000.0);
		accountThree.deposit(3000.0);

		Client client("John Smith");

		client.addAccount(accountOne);
		client.addAccount(accountTwo);
		client.addAccount(accountThree);

		double totalBalance = 0.0;

		/*
		for (vector<BankAccount>::iterator iter = client.iteratorBegin(); iter!=client.iteratorEnd(); iter++) {
			totalBalance += iter->getBalance();
			//cout<<"debugging"<<iter->getBalance()<<endl;
		}*/

		for (vector<BankAccount>::size_type index = 0; index!=client.getNumberOfAccounts(); index++) {
					totalBalance += client[index].getBalance();
					//cout<<"debugging"<<iter->getBalance()<<endl;
		}
		if (totalBalance != 6000.0) {
			cout<<totalBalance<<"** Test failure"<<endl;
		}
		    cout<<"done"<<endl;
		return 0;
	}


/*!End Snippet:file*/
