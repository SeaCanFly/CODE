#include<cstdio>
#include<iostream>
#include<cstring>
#include<memory.h>
#include<cstdlib>
using namespace std;
int StrLen(const char* str)
{
	int i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return i;
}
char* StrCpy(char* d, const char* s)
{

	d = (char*)malloc(StrLen(s) + 1);
	char* temp = d;
	while (*temp++ = *s++);

	return d;
}
char* StrCat(const char* str1, const char* str2)
{
	char* add = (char*)malloc(strlen(str1) + strlen(str2) + 1);
	char* temp = add;
	while (*str1)
	{
		*temp++ = *str1++;
	}
	while (*temp++ = *str2++);

	return add;
}
int StrCmp(const char* str1, const char* str2)
{
	if (str1==NULL || str2==NULL)return -1;
		while (*str2&&(*str1 == *str2))
		{
			str1++; str2++;
		}
	return *str1 - *str2;
}
int StrCmpN(const char* str1, const char* str2, int n)
{
	while (*str2&&(*str1 == *str2)&&n--)
	{
		str1++; str2++;
	}
	return *str1-*str2;
}
char* StrRev(char *str)
{
	char* head = str;
	char t;
	char* tail = str + StrLen(str)-1;
	while(head<tail)
	{
		t = *head;
		*head= *tail;
		*tail= t;
		tail--; head++;
	}
	return str;
}
int FindStr(const char* d, char* s)
{
	int count = 0;
	char* temp = s;
	while (*d)
	{
		if (*d == *s)
		{
			temp = s;
			do
			{
				temp++;
				if (*temp == '\0')
				{
					count++;
					cout << count << ":" << d << endl;
					break;
				}
				d++;
			} while (*d == *temp);
		}
		else
		{
			d++;
		}
	}
	return count;
}
int StrChr(const char* str, const char* c)
{
	int count = 0;
	while (*str)
	{
		if (*str == *c)
		{
			count++;
			cout <<count<<":"<< str << ",";
		}
		str++;
	}
	cout << endl;
	return count;
}
bool IsNum(const char* str)
{
	if (*str - '0' >= 0 && *str - '9' <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int TakeNum(const char* str)
{
	int num = 0;
	while (*str)
	{
		if (IsNum(str))
		{
			while (IsNum(str))
			{
				cout << *str;
				str++;
			}
			num++;
			cout << ",";
		}
		else
		{
			str++;
		}
	}
	return num;
}
int NumAdd(const char* str)
{
	int sum = 0;
	while (*str)
	{
		if (IsNum(str))
		{
			sum = sum + (*str-'0');
		}
		str++;
	}
	return sum;
}
