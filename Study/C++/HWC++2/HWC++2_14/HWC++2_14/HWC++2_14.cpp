/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_14
Visual Studio 2015
*/
#include<iostream>
#include<string>
using namespace std;
#define MAX 1000
int main()
{
	char a[MAX] = { 0 }, ctemp;
	int check[26] = { 0 };
	cout << "Input English articles,with a';'to end\nMaximum 1000 words." << endl;
	cin.getline(a, MAX, ';');
	for (int i = 0; i < MAX; i++)
	{
		if (isalpha(a[i]))
		{
			ctemp = tolower(a[i]);
			if ((ctemp - 'a') >= 0 && (ctemp - 'a') < 26)
			{
				check[ctemp - 'a']++;
			}	
		}
	}
	for (int i = 0; i < 26; i++)
	{
		cout << char('a' + i) << "(" << check[i] << ")" << "\t:";
		for (int j = 0; j < check[i]; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	return 0;
}