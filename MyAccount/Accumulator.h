#ifndef _ACCUMULATOR_H_
#define _ACCUMULATOR_H_
#include "Date.h"

class Accumulator
{
public:
	Accumulator(const Date &date, double value) :lastDate(date), value(value), sum(0) {}
	double getSum(const Date &date)
	{
		return sum + value*date.distance(lastDate);
	}
	void change(const Date &date, double value)
	{
		sum = getSum(date);
		lastDate = date;
		this->value = value;
	}

	void reset(const Date&date, double value)
	{
		lastDate = date;
		this->value = value;
		sum = 0;
	}

private:
	Date lastDate;
	double value, sum;
};


#endif // !_ACCUMULATOR_H_

