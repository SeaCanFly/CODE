#include"HW3_8.h"
void Add::setValue(int x, int y)
{
	a = x; b = y;
}
void Sub::setValue(int x, int y)
{
	a = x; b = y;
}
void Mul::setValue(int x, int y)
{
	a = x; b = y;
}
void Div::setValue(int x, int y)
{
	a = x; b = y;
}
int Add::calculate()
{
	return a + b;
}
int Sub::calculate()
{
	return a - b;
}int Mul::calculate()
{
	return a * b;
}int Div::calculate()
{
	return a / b;
}