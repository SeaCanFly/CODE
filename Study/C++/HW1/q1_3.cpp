#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;
int findstr(const char* str1, char* str2)
{
	int count = 0;char*temp = str2;
	while (*str1)
	{
		if (*str1 == *str2)
		{
				temp = str2;
				while (*str1 == *temp)
				{
					temp++;
					if (*temp=='\0')
					{
						count++;
						break;
					}
					str1++;
				} 
		}
		else
		{
			str1++;
		}
		
	}
	return count;
}
int main()
{
	int n = findstr("aabab", "ab");
	cout << n << endl;
	return 0;
}