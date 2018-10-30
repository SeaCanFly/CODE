#include"HW3_10.h"
#include<iostream>
using namespace std;
Ram::Ram()
{
	mem[100 * 1024] = { 0 };
	size = 100 * 1024;
}
Ram::~Ram()
{
	cout << "Memory Release" << endl;
}
char Ram::read(int address)
{
	return mem[address];
}
void Ram::write(int address, char value)
{
	mem[address] = value;
}