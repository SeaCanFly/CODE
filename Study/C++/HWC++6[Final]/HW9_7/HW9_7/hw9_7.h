#pragma once
#include<string>
#include<iostream>
using namespace std;
class Shape
{
protected:
	string name;
	int width, height;
public:
	Shape(string n = "", int w = 0, int h = 0) :name(n), width(w), height(h) {}
	virtual double getArea() { return 0; }
	string getName() { return name; }
};
class Oval :public Shape
{
public:
	Oval(string n="",int w=0,int h=0):Shape(n,w,h){}
	double getArea()
	{
		return 3.14*width*height;
	}
};
class Rect :public Shape
{
public:
	Rect(string n="",int w=0,int h=0):Shape(n,w,h){}
	double getArea()
	{
		return width*height;
	}
};
class Triangular :public Shape
{
public:
	Triangular(string n="",int w=0,int h=0):Shape(n,w,h){}
	double getArea()
	{
		return width*height / 2;
	}
};