#pragma once
#include<string>
#include<iostream>
using namespace std;
class Circle
{
	int mi_radius;
public:
	Circle(int i_radius=0):mi_radius(i_radius){}
	int getRadius() { return mi_radius; }
	void setRadius(int i_radius) { mi_radius = i_radius; }
	double getArea() { return 3.14*mi_radius*mi_radius; }
};
class NamedCiarcle:public Circle
{
	string ms_name;
public:
	NamedCiarcle(int i_radius, string pc_name) :Circle(i_radius), ms_name(pc_name) {}
	void fShow()
	{
		cout << "r=" << getRadius() << ' ' << ms_name << endl;
	}
};