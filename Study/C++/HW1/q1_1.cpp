#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;

int main()
{
	
	string name[5],maxn;
	int m[5] = { 0 },max;
	cout << "input 5 names:";
	for (int i = 0; i < 5; i++)
	{
		getline(cin, name[i], ';');
		m[i] = name[i].size();
	}
	max = m[0];
	for (int i = 1; i < 5; i++)
	{
		if (m[i] > max)
		{
			max = m[i];
			maxn = name[i];
		}
	}
	cout << maxn << endl;
	return 0;
}