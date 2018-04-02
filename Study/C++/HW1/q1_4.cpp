#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;
int a(char* str)
{
	char temp;
	char* t = str;
	while (*t)
	{
		temp = *t;
		char* ct = t;
		while (*ct!='\0')
		{
			ct++;
			if (temp == *ct)
			{
				return 1;
			}
		}
		t++;
	}
	return 0;
}
int main()
{
	char* s1 = "acabj";
	cout << a(s1) << endl;
	
	return 0;
}