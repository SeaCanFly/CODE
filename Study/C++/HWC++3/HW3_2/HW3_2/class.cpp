#include"HW3_2.h"
#include<iostream>
using namespace std;
Date::Date(int y, int m, int d)
{
	year = y; month = m; day = d;
}
Date::Date(const char* s)
{
	char* temp = (char*)s;
	int n = 3;
	while (n)
	{
		int value = 0;
		while ((temp != '\0') && (*temp - '0' < 0) || (*temp - '9' > 0))
		{
			temp++;
		}
		while ((temp != '\0') && (*temp - '0' >= 0) && (*temp - '9' <= 0))
		{
			value = value * 10 + (*temp - '0');
			temp++;
		}
		if (n == 3)
		{
			year = value;
		}
		if (n == 2)
		{
			month = value;
		}
		if (n == 1)
		{
			day = value;
		}
		n--;
	}

}
int Date::getYear()
{
	return year;
}
int Date::getMonth()
{
	return month;
}
int Date::getDay()
{
	return day;
}
void Date::show()
{
	cout << year << "year-" << month << "month-" << day << "day" << endl;
}