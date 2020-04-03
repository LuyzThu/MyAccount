// MyAccount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"

using namespace std;


int main()
{
	Date date(2008, 11, 1);
	SavingAccount sa1(date, "S3755217", 0.015);
	SavingAccount sa2(date, "01235486", 0.015);
	CreditAccount ca(date, "C5392394", 0.0005, 10000, 50);

	sa1.deposit(Date(2008, 11, 5), 5000, "salary");
	ca.withdraw(Date(2008, 11, 15), 2000, "shopping");
	sa2.deposit(Date(2008, 11, 25), 10000, "sell stock");

	ca.settle(Date(2008, 12, 1));

	ca.deposit(Date(2008, 12, 1), 2016, "repay");
	sa1.deposit(Date(2008, 12, 5), 5500, "salary");

	sa1.settle(Date(2009, 1, 1));
	sa2.settle(Date(2009, 1, 1));
	ca.settle(Date(2009, 1, 1));

	cout << endl;
	sa1.show(); cout << endl;
	sa2.show(); cout << endl;
	//ca.show(); cout << endl;

	cout << "Total: " << Account::getTotal() << endl;

    return 0;
}

