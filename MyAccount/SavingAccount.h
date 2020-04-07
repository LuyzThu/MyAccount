#ifndef _SAVING_ACCOUNT_H_
#define _SAVING_ACCOUNT_H_

#include <string>
#include "Date.h"
using namespace std;

class SavingAccount
{
public:
	SavingAccount(Date date, string id, double rate);
	string getId() const { return id; }
	double getBalance() const{ return balance; }
	double getRate() const { return rate; }
	void show() const;

	void deposit(Date date, double amount, string desc);
	void withdraw(Date date, double amount, string desc);
	void settle(Date date);
	static double getTotal() { return total; }

private:
	string id;
	double balance, rate, accumulation;
	static double total;
	Date lastDate;
	void record(Date date, double amount, string desc);
	void error(string msg) const;
	double accumulate(Date date) const
	{
		return accumulation + balance * (date - lastDate);
	}

};



#endif // !_SAVING_ACCOUNT_H_
#pragma once
