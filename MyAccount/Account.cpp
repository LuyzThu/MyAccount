#include "stdafx.h"
#include "Account.h"
#include <iostream>
#include <cmath>

double Account::total = 0;


Account::Account(const Date &date, const string &id) :balance(0), id(id)
{
	date.show();
	cout << "\t#" << id << " created" << endl;
}

void Account::record(const Date &date, double amount, const string &desc)
{
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void Account::show() const
{
	cout << id << "\tBalance:" << balance;
}

void Account::error(const string &msg) const
{
	cout << "Error(#" << id << "):" << msg << endl;
}

SavingAccount::SavingAccount(const Date &date, const string &id, double rate) :Account(date, id), acc(date, 0), rate(rate) {}

void SavingAccount::withdraw(const Date &date, double amount, const string &desc)
{
	if (amount>getBalance())
	{
		error("No enough money");
	}
	else
	{
		record(date, -amount, desc);
		acc.change(date, getBalance());
	}
}

void SavingAccount::deposit(const Date &date, double amount, const string &desc)
{
	record(date, amount, desc);
	acc.change(date, getBalance());
}

void SavingAccount::settle(const Date &date)
{
	double interest = acc.getSum(date)*rate
		/ date.distance(Date(date.getYear() - 1, 1, 1));
	if (interest != 0)
	{
		record(date, interest, "interest");
	}
	acc.reset(date, getBalance());
}

CreditAccount::CreditAccount(const Date &date, const string &id, double rate, double credit, double fee)
	:Account(date, id), credit(credit), rate(rate), fee(fee), acc(date, 0){}

void CreditAccount::deposit(const Date &date, double amount, const string &desc)
{
	record(date, amount, desc);
	acc.change(date, getDebt());
}

void CreditAccount::withdraw(const Date &date, double amount, const string &desc)
{

	if ((amount - getBalance()) > credit)
	{
		error("No enough credit");
	}
	else
	{
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}

void CreditAccount::settle(const Date &date)
{
	double interest = acc.getSum(date)*rate;
	if (interest != 0)
	{
		record(date, interest, "interest");
	}
	if (date.getMonth() == 1)
	{
		record(date, -fee, "annual fee");
	}
	acc.reset(date, getDebt());
}

void CreditAccount::show() const
{
	Account::show();
	cout << "\tAvailable credit: " << getAvailableCredit();
}