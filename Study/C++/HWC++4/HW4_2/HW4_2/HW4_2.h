#pragma once
#include<iostream>
using namespace std;
class Sample
{
private:
	int* p;
	int size;
public:
	Sample(int n) :size(n), p(new int[n]) {};
	void read()
	{
		for (int i = 0; i < size; i++)
		{
			cin >> p[i];
		}
	}
	void write()
	{
		for (int i = 0; i < size; i++)
		{
			cout << p[i] << ' ';
		}
		cout << endl;
	}
	int big()
	{
		int big = p[0];
		for (int i = 0; i < size; i++)
		{
			if (big < p[i])
			{
				big = p[i];
			}
		}
		return big;
	}
	~Sample() { delete[]p; };
};