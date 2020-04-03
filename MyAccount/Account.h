#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "Date.h"
#include "Accumulator.h"
#include <string>

using namespace std;

class Account
{
public:
	Account(const Date &date, const string &id);
	void record(const Date &date, double amount, const string &desc);
	void error(const string &msg) const;
	const string &getId() const { return id; }
	double getBalance() const { return balance; }
	static double getTotal() { return total; }
	void show() const;

private:
	string id;
	double balance;
	static double total;
};

class SavingAccount :public Account
{
public:
	SavingAccount(const Date &date, const string &id, double rate);
	double getRate() const { return rate; }
	void deposit(const Date &date, double amount, const string &desc);
	void withdraw(const Date &date, double amount, const string &desc);
	void settle(const Date &date);


private:
	Accumulator acc;
	double rate;
};

class CreditAccount :public Account
{
public:
	CreditAccount(const Date &date, const string &id, double rate, double credit, double fee);
	double getCredit() const { return credit; }
	double getRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvailableCredit() const
	{
		if (getBalance() < 0)
		{
			return credit + getBalance();
		}
		else
		{
			return credit;
		}
	}
	void deposit(const Date &date, double amount, const string &desc);
	void withdraw(const Date &date, double amount, const string &desc);
	void settle(const Date &date);
	void show() const;

private:
	Accumulator acc;
	double credit, rate, fee;
	double getDebt() const
	{
		double balance = getBalance();
		return (balance < 0 ? balance : 0);
	}
};











#endif // !_ACCOUNT_H_