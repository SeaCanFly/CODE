/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_13
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
#define MAX 100
int main()
{
	char a[MAX], b[MAX],c;
	while (1)
	{
		cout << "? ";
		cin.getline(a, MAX, ' ');
		cin >> c;
		cin.getline(b, MAX, '\n');

		switch (c)
		{
		case '+':cout << a <<" "<< c << b << " = " << atoi(a) + atoi(b) << endl;
			break;
		case '-':cout << a <<" "<< c << b << " = " << atoi(a) - atoi(b) << endl;
			break;
		case '*':cout << a <<" "<< c << b << " = " << atoi(a)*atoi(b) << endl;
			break;
		case '/':cout << a <<" "<< c << b << " = " << atoi(a) / atoi(b) << endl;
			break;
		case '%':cout << a <<" "<< c << b << " = " << atoi(a) % atoi(b) << endl;
			break;
		default: goto end;
		}
	}
	end:

	return 0;
}