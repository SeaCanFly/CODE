#include<cstdio>
#include<iostream>
#include<string.h>
#include<memory.h>
#include<stdlib.h>
using namespace std;
char* StrCpy(char* d, const char* s)
{
	
	d = (char*)malloc(sizeof(char)*(strlen(s)+1));
	char* temp = d;
	while (*temp++ = *s++);

	return d;
}
char* StrCat(const char* a, const char* b)
{
	char* add = (char*)malloc(strlen(a)+strlen(b)+1);
	char* temp = add;
	while (*a)
	{
		*temp++=*a++;
	}
	while (*temp++ = *b++);

	return add;
}
int main()
{
	char* a = "hello neet to meet you!";
	char b[50] = "world sleep";
	char* c = "to define";

	char* re = strcat(b, a);

	cout << a << endl;
	cout << b << endl;
	cout << StrCpy(b, a) << endl;

	cout << StrCat(a, b) << endl;
		return 0;
}
