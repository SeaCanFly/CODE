/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_5
Visual Studio 2015
*/
#include<iostream>
using namespace std;
#define MAX 100
int main()
{
	char a[MAX] = { 0 };
	int n = 0;
	cin.getline(a, MAX);
	for (int i = 0; i < MAX; i++)
	{
		if (a[i] == 'x' || a[i] == 'X')
		{
			n++;
		}
	}
	cout << "The number of x:" << n << endl;
	return 0;
}