#ifndef  _DATE_H_
#define _DATE_H_

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




#endif // ! _DATE_H_
