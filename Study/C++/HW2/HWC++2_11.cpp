/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #2_11
Visual Studio 2015
*/
#include<iostream>
using namespace std;
int main()
{
	int k, n = 0;
	int sum = 0;
	cout << "Enter the number of cutoffs>>";
	cin >> n;
	for (k = 1; k <= n; k++)
	{
		sum += k;
	}
	cout << "From 1 add up to " << n << " total:" << sum << endl;
	return 0;
}