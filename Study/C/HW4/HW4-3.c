/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_3
Visual Studio 2015
*/

#include <stdio.h>
int main()
{
	char name[10] = { '\0' }; char a[100] = { '\0' }; int c;
	printf("what's your name?\n>");
	gets(name);
	printf("%s,What do you want to say?\n>",name);
	while (gets(a) != NULL)
	{
		printf("%s, %s is a good topic\n",name,a);
		printf("Intersting, Would like to say something more?\n>");
	}
	return 0;
}
