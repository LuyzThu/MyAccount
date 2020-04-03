#include "stdafx.h"
#include "Date.h"

#include <iostream>
using namespace std;

namespace
{
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
}

Date::Date(int year, int month, int day) :year(year), month(month), day(day)
{
	if (day<=0||day>getMaxDay())
	{
		cout << "Invalid date" << endl;
		show();
		exit(1);
	}
	int years = year - 1;
	totalDays = years * 365 + years / 4 - years / 100 + year / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
	if (isLeapYear()||month>2)
	{
		totalDays++;
	}
}

bool Date::isLeapYear() const
{
	return year % 4 == 0 && year != 100 || year % 400 == 0;
}

int Date::getMaxDay() const
{
	if (isLeapYear() && month == 2)
	{
		return 29;
	}
	else
	{
		return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
	}
}

void Date::show() const
{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
