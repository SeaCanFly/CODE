/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_3
Visual Studio 2015
*/

#include<iostream>
using namespace std;
class MyTime
{
public:
	int hour, minute, second;
	MyTime();
	MyTime(int , int , int );
	~MyTime() {}
	void print();
	MyTime add(MyTime );
};