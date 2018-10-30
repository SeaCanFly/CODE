#pragma once
#include<iostream>
#include<string>
using namespace std;
class LoopAdder
{
	string name;
	int x, y, sum;
	void read();
	void write();
protected:
	LoopAdder(string name = "") :name(name) {}
	int getX() { return x; }
	int getY() { return y; }
	virtual int calculate() = 0;
public:
	void run();
};
void LoopAdder::read()
{
	cout << name << ":" << endl;
	cout << "Input the first number,and the second number>>";
	cin >> x >> y;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore();
		cin >> x >> y;
	}
}
void LoopAdder::write()
{
	cout << x << "to" << y << " sum=" << sum << endl;
}
void LoopAdder::run()
{
	read();
	sum = calculate();
	write();
}
class ForLoopAdder :public LoopAdder
{
public:
	ForLoopAdder(string s_name) :LoopAdder(s_name) {}
	int calculate()
	{
		int temp = 0;
		for (int i = getX(); i <= getY(); i++)
		{
			temp += i;
		}
		return temp;
	}
};