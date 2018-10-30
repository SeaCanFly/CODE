/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_12
Visual Studio 2015
*/
#include<iostream>
using namespace std;
int sum(int ,int );
int main()
{
	int n = 0;
	cout << "Enter the number of cutoffs>>";
	cin >> n;
	cout << "From 1 add up to " << n << " total:" << sum(1, n) << endl;
	return 0;
}
int sum(int a, int b)
{
	int k, res = 0;
	for (k = a; k <= b; k++)
	{
		res += k;
	}
	return res;
}