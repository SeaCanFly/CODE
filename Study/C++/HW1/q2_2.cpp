#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
using namespace std;
char* SC(char * s1, const char* s2)
{
	while (*s1++ = *s2++);
	return s1;
}
char m[200] = { 0 };
char* cs(char*str)
{
	int j = 0;
	int n = strlen(str);
	for (int i = 0; i < n;i++)
	{
		if (str[i] == ' ')
		{
			m[j] = '%';
			m[j + 1] = '2';
			m[j + 2] = '0';
			j = j + 3;
		}
		else if (str[i] == '\0')
		{
			m[j] = '\0';
		}
		else
		{
			m[j] = str[i];
			j++;
		}
	}
	return m;
}
int main()
{
	char input[100] = "hello world. Nice to meet you.";
	char * s = cs(input);
	printf("%s\n", s);
	return 0;
}