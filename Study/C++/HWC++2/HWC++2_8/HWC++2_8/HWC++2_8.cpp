/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_8
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a[5], max;
	int m[5], temp;
	cout << "Enter 5 names, and to distinguish between ';'." << endl << ">>";
	for (int i = 0; i < 5; i++)
	{
		getline(cin, a[i], ';');
		m[i] = a[i].size();
	}
	temp = m[0];
	for (int i = 0; i < 5; i++)
	{
		cout << i + 1 << ":" << a[i] << endl;
		if (m[i] >= temp)
		{
			temp = m[i];
			max = a[i];
		}
	}
	cout << "The longest name is:" << max << endl;
	return 0;
}