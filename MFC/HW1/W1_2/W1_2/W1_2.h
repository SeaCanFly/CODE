/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_2
Visual Studio 2015
*/

#include<iostream>
#include<math.h>
using namespace std;
class CMyPoint
{
public:
	int x, y;
	CMyPoint();
	CMyPoint(int , int );
	~CMyPoint() {}
	float distance(CMyPoint );
	void print();
};