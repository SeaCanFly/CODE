/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #8_7
Visual Studio 2015
*/
#include"hw8_7.h"
#include<iostream>
using namespace std;
int main()
{
	char x[5] = { 'h','e','l','l','o' };
	ROM biosROM(1024 * 10, x, 5);
	RAM mainMemory(1024 * 1024);
	for (int i = 0; i < 5; i++)
	{
		mainMemory.fWrite(i, biosROM.fRead(i));
	}
	for (int i = 0; i < 5; i++)
	{
		cout << mainMemory.fRead(i);
	}
	return 0;
}