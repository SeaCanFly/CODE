/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_9
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string name, add; char a;
	cout << "Enter your name:";
	getline(cin, name);
	cout << "Enter your address:";
	getline(cin, add);
	cout << "Enter your age:";
	cin >> a;
	cout << name << "," << add << "," << a << " years old" << endl;
	return 0;
}