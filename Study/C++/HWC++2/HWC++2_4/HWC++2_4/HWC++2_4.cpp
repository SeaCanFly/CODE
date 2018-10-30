/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_4
Visual Studio 2015
*/
#include<iostream>
using namespace std;
int main()
{
	float a[5], max;
	cout << "Enter 5 real numbers:>";
	for (int i = 0; i < 5; i++)
	{
		cin >> a[i];
	}
	max = a[0];
	for (int i = 1; i < 5; i++)
	{
		if (a[i] >= max)
		{
			max = a[i];
		}
	}
	cout << "The largest number=" << max << endl;
	return 0;
}