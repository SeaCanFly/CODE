/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_4
Visual Studio 2015
*/

#include<iostream>
using namespace std;
class MyShape
{
public:
	int x, y;
	MyShape();
	MyShape(int , int );
	~MyShape() {};
	virtual void draw();
};
class MyRect :public MyShape
{
public:
	int w, h;
	MyRect();
	MyRect(int , int , int , int );
	~MyRect() {}
	void draw();
};
class MyCircle :public MyShape
{
public:
	int r;
	MyCircle();
	MyCircle(int , int , int );
	~MyCircle() {}
	void draw();
};