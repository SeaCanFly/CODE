/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_10
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a;
	int i = 0;
	cout << "Input a string>>";
	getline(cin, a);
	while (a[i] != NULL)
	{
		for (int j = 0; j <= i; j++)
		{
			cout << a[j];
		}
		cout << endl;
		i++;
	}
	return 0;
}