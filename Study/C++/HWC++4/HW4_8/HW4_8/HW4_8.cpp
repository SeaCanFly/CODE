/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_8
Visual Studio 2015
*/

#include"HW4_8.h"
int main()
{
	Family* simpson = new Family("Simpson", 3);
	simpson->setName(0, "Mr. Simpson");
	simpson->setName(1, "Mrs. Simpson");
	simpson->setName(2, "Bart Simpson");
	simpson->show();
	delete simpson;
	return 0;
}