#include "stdafx.h"
#include "SavingAccount.h"

#include <iostream>
#include <string>

using namespace std;

double SavingAccount::total = 0;

SavingAccount::SavingAccount(Date date, string id, double rate)
	:id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	date.show();
	cout << "\t" << id << " created" << endl;
}

void SavingAccount::record(Date date, double amount, string desc)
{
	accumulation = accumulate(date);
	lastDate = date;
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void SavingAccount::error(string msg) const
{
	cout << "Error(#" << id << "):" << msg << endl;
}

void SavingAccount::deposit(Date date, double amount,string desc)
{
	record(date, amount, desc);
}

void SavingAccount::withdraw(Date date, double amount, string desc)
{
	if (amount>balance)
	{
		error("No enough money");
	}
	else
	{
		record(date, -amount, desc);
	}
}

void SavingAccount::settle(Date date)
{
	double interest = accumulate(date)*rate / date.distance(Date(date.getYear() - 1, 1, 1));
	if (interest != 0)
	{
		record(date, interest, "interest");
	}
	accumulation = 0;
}

void SavingAccount::show() const
{
	cout << id << "\tBalance:" << balance << endl;
}