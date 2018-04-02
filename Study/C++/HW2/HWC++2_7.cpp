/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_7
Visual Studio 2015
*/
#include<iostream>
using namespace std;
#define MAX 10
int main()
{
	char a[MAX] = { 0 };
	while (1)
	{
		cout << "Input \"yes\" to exit>>";
		cin.getline(a, MAX);
		if (strcmp(a,"yes")==0)
		{
			break;
		}
	}
	cout << "End" << endl;
	return 0;
}