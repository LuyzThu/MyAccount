// MyAccount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "MyArray.h"

using namespace std;


int main()
{
	Date date(2008, 11, 1);

	/*SavingAccount sa1(date, "S3755217", 0.015);
	SavingAccount sa2(date, "01235486", 0.015);
	CreditAccount ca(date, "C5392394", 0.0005, 10000, 50);

	Account* accounts[] = { &sa1,&sa2,&ca };
	int n = sizeof(accounts) / sizeof(Account*);*/

	MyArray<Account*> accounts(0);
	cout << "(d)deposit (w)withdraw (s)show (c)change day (n)next month (e)exit" << endl;
	char cmd;
	do
	{
		date.show();
		cout << "\tTotal: " << Account::getTotal() << "\tcommand>";
		char type;
		int index, day;
		double amount, credit, rate, fee;
		string id, desc;
		Account* account;
		cin >> cmd;
		switch (cmd)
		{
		case 'a':
			cin >> type >> id;
			if (type == 's')
			{
				cin >> rate;
				account = new SavingAccount(date, id, rate);
			}
			else
			{
				cin >> credit >> rate >> fee;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			accounts.resize(accounts.getSize() + 1);
			accounts[accounts.getSize() - 1] = account;
			break;
		case 'd':
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
			for (int i = 0; i < accounts.getSize(); i++)
			{
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':
			cin >> day;
			if (day<date.getDay())
			{
				cout << "Err: previous day";
			}
			else if (day>date.getMaxDay())
			{
				cout << "Invalid day";
			}
			else
			{
				date = Date(date.getYear(), date.getMonth(), day);
			}
			break;
		case 'n':
			if (date.getMonth() == 12)
				date = Date(date.getYear() + 1, 1, 1);
			else
			{
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}
			for (int i = 0; i < accounts.getSize(); i++)
			{
				accounts[i]->settle(date);
			}
			break;
		default:
			break;
		}








	} while (cmd!='e');
	for (int i = 0; i < accounts.getSize(); i++)
	{
		delete accounts[i];
	}


    return 0;
}

