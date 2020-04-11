// MyAccount.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Controller.h"


using namespace std;

void main()
{
	Date date(2008, 11, 1);
	Controller controller(date);
	string cmdLine;
	const char* FILE_NAME = "cmd.txt";
	ifstream fileIn(FILE_NAME);
	if (fileIn)
	{
		while (getline(fileIn, cmdLine))
			controller.runCommand(cmdLine);
		fileIn.close();
	}
	ofstream fileOut(FILE_NAME, ios_base::app);
	cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
	while (!controller.isEnd())
	{
		cout << controller.getDate() << "\tTotal:" << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		if (controller.runCommand(cmdLine))
		{
			fileOut << cmdLine << endl;
		}
	}
	return;
}




























//int main()
//{
//	Date date(2008, 11, 1);
//
//	/*SavingAccount sa1(date, "S3755217", 0.015);
//	SavingAccount sa2(date, "01235486", 0.015);
//	CreditAccount ca(date, "C5392394", 0.0005, 10000, 50);
//
//	Account* accounts[] = { &sa1,&sa2,&ca };
//	int n = sizeof(accounts) / sizeof(Account*);*/
//
//	//MyArray<Account*> accounts(0);
//
//	vector<Account*>accounts;
//	cout << "(d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;
//	char cmd;
//	do
//	{
//		date.show();
//		cout << "\tTotal: " << Account::getTotal() << "\tcommand>";
//		char type;
//		int index, day;
//		double amount, credit, rate, fee;
//		string id, desc;
//		Account* account;
//		Date date1, date2;
//		cin >> cmd;
//		switch (cmd)
//		{
//		case 'a':
//			cin >> type >> id;
//			if (type == 's')
//			{
//				cin >> rate;
//				account = new SavingAccount(date, id, rate);
//			}
//			else
//			{
//				cin >> credit >> rate >> fee;
//				account = new CreditAccount(date, id, credit, rate, fee);
//			}
//			accounts.push_back(account);
//			break;
//		case 'd':
//			cin >> index >> amount;
//			getline(cin, desc);
//			accounts[index]->deposit(date, amount, desc);
//			break;
//		case 'w':
//			cin >> index >> amount;
//			getline(cin, desc);
//			accounts[index]->withdraw(date, amount, desc);
//			break;
//		case 's':
//			for (int i = 0; i < accounts.size(); i++)
//			{
//				cout << "[" << i << "]";
//				accounts[i]->show();
//				cout << endl;
//			}
//			break;
//		case 'c':
//			cin >> day;
//			if (day<date.getDay())
//			{
//				cout << "Err: previous day";
//			}
//			else if (day>date.getMaxDay())
//			{
//				cout << "Invalid day";
//			}
//			else
//			{
//				date = Date(date.getYear(), date.getMonth(), day);
//			}
//			break;
//		case 'n':
//			if (date.getMonth() == 12)
//				date = Date(date.getYear() + 1, 1, 1);
//			else
//			{
//				date = Date(date.getYear(), date.getMonth() + 1, 1);
//			}
//			for (vector<Account*>::iterator iter = accounts.begin();iter != accounts.end();++iter)
//			{
//				(*iter)->settle(date);
//			}
//			break;
//		case 'q':
//			date1 = Date::read();
//			date2 = Date::read();
//			Account::query(date1, date2);
//			break;
//		default:
//			break;
//		}
//
//	} while (cmd!='e');
//	for_each(accounts.begin(), accounts.end(), deleter());
//
//
//    return 0;
//}

