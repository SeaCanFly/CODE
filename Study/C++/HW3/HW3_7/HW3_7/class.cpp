#include"HW3_7.h"
#include<iostream>
Oval::Oval()
{
	width = 1; height = 1;
}
Oval::Oval(int x, int y)
{
	width = x; height = y;
}
Oval::~Oval()
{
	std::cout << "Oval destructor: width=" << width << ',' << "height=" << height <<std::endl;
}
int Oval::getHeight()
{
	return height;
}
int Oval::getWidth()
{
	return width;
}
void Oval::set(int x,int y)
{
	width = x; height = y;
}
void Oval::show()
{
	std::cout << "width=" << width << ',' << "height=" << height <<std::endl;
}