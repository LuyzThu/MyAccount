#ifndef  _DATE_H_
#define _DATE_H_

#include <iostream>
using namespace std;

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getMaxDay() const;
	bool isLeapYear() const;
	void show() const;
	//static Date read();

	bool operator<(const Date& date) const
	{
		return totalDays < date.totalDays;
	}

	/*int distance(Date date) const
	{
		return totalDays - date.totalDays;
	}*/

	int operator- (const Date& date) const
	{

		return totalDays - date.totalDays;
	}

private:
	int year, month, day, totalDays;
};

istream& operator>>(istream& in, Date& date);

ostream& operator<<(ostream& in, const Date& date);


#endif // ! _DATE_H_
