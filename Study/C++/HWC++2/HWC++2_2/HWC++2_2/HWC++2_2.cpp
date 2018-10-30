/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_2
Visual Studio 2015
*/
#include<iostream>
using namespace std;
int main()
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = 1; j < 10; j++)
		{
			cout << j << "x" << i << "=" << i*j << "\t";
		}
		cout << endl;
	}
	return 0;
}