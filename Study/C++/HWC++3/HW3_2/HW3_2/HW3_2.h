#pragma once
class Date
{
private:
	int year, month, day;
public:
	void show();
	int getYear();
	int getMonth();
	int getDay();
	Date(int, int, int);
	Date(const char*);

};