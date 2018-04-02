#pragma once
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class Circle
{
	string name;
	int radius;
public:
	Circle(int radius, string name) :radius(radius), name(name) {}
	double getArea() { return 3.14*radius*radius; }
	string getName() { return name; }
};