#pragma once
#include<iostream>
#include<string>
using namespace std;
class Histogram
{
private:
	string str0;
public:
	Histogram(string str):str0(str){}
	void put(string str)
	{
		str0 += str;
	}
	void putc(char c)
	{
		str0 += c;
	}
	void print()
	{
		cout << str0 << endl;
		int size = str0.size();	int check[26] = { 0 };
		for (int i = 0; i < size; i++)
		{
			char ctemp=tolower(str0[i]);
			if (isalpha(ctemp))
			{
				if (ctemp - 'a' >= 0 && ctemp - 'z' <= 0)
				{
					check[ctemp - 'a']++;
				}
			}
		}
		
		for (int i = 0; i < 26; i++)
		{
			cout << (char)( i + 'a' ) << '(' << check[i] << ')' << ":";
			for (int j = 0; j < check[i]; j++)
			{
				cout << '*';
			}
			cout << endl;
		}
	}
};