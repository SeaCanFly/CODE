/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #8_9
Visual Studio 2015
*/
#include"hw8_9.h"
int main()
{
	AirLine* airbook=new AirLine;
	Console console(airbook);
	console.fSelect();
	delete airbook;
	return 0;
}