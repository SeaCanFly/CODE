/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_6
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a, b;
	cout << "Enter your password>>";
	getline(cin, a);
	cout << "Re-enter the password>>";
	getline(cin, b);
	if (a == b)
	{
		cout << "Enter the same" << endl;
	}
	else
	{
		cout << "The input is different!" << endl;
	}
	return 0;
}