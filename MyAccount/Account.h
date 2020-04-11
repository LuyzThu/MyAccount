#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "Date.h"
#include "Accumulator.h"
#include <string>
#include <map>
#include <istream>

using namespace std;

class Account;

class AccountRec
{
public:
	AccountRec(const Date& date, const Account* account, double amount, double balance, const string& desc);
	void show();

private:
	Date date;
	const Account* account;
	double amount;
	double balance;
	string desc;
};



typedef multimap<Date, AccountRec>RecordMap;
class Account
{
public:
	Account(const Date &date, const string &id);
	void record(const Date &date, double amount, const string &desc);
	void error(const string &msg) const;
	const string &getId() const { return id; }
	double getBalance() const { return balance; }
	static double getTotal() { return total; }
	virtual void deposit(const Date& date, double amount, const string& desc) = 0;
	virtual void withdraw(const Date& date, double amount, const string& desc) = 0;
	virtual void show(ostream& out) const;
	virtual void settle(const Date& date) = 0;
	static void query(const Date& begin, const Date& end);

private:
	string id;
	double balance;
	static double total;
	static RecordMap recordMap;
};

inline ostream& operator<<(ostream& out, const Account& account)
{
	account.show(out);
	return out;
}
class SavingAccount :public Account
{
public:
	SavingAccount(const Date &date, const string &id, double rate);
	double getRate() const { return rate; }
	void deposit(const Date& date, double amount, const string& desc);
	void withdraw(const Date& date, double amount, const string& desc);
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
	void show(ostream& out) const;

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
