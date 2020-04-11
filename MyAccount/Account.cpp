#include "stdafx.h"
#include "Account.h"
#include <iostream>
#include <cmath>
#include <utility>

using namespace rel_ops;

AccountRec::AccountRec(const Date& date, const Account* account, double amount, double balance, const string& desc)
	:date(date), account(account), amount(amount), balance(balance), desc(desc)
{}

void AccountRec::show()
{
	//date.show();

	cout << date << "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}








double Account::total = 0;
RecordMap Account::recordMap;

Account::Account(const Date &date, const string &id) :balance(0), id(id)
{
	//date.show();
	cout << date << "\t#" << id << " created" << endl;
}

void Account::record(const Date &date, double amount, const string &desc)
{
	amount = floor(amount * 100 + 0.5) / 100;
	balance += amount;
	total += amount;
	date.show();
	AccountRec accRec(date, this, amount, balance, desc);
	recordMap.insert(make_pair(date, accRec));
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}

void Account::show(ostream& out) const
{
	out << id << "\tBalance:" << balance;
}

void Account::error(const string &msg) const
{
	cout << "Error(#" << id << "):" << msg << endl;
}

void Account::query(const Date& begin, const Date& end)
{
	if (begin <= end)
	{
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);
		RecordMap::iterator iter2 = recordMap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; ++iter)
		{
			iter->second.show();
		}
	}
}




//SavingAccount

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
	if (date.getMonth() == 1)
	{
		double interest = acc.getSum(date) * rate
			/ (date - Date(date.getYear() - 1, 1, 1));
		if (interest != 0)
		{
			record(date, interest, " interest");
		}
		acc.reset(date, getBalance());
	}
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

void CreditAccount::show(ostream& out) const
{
	Account::show(out);
	cout << "\tAvailable credit: " << getAvailableCredit();
}