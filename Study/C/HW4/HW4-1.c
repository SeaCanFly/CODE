/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_1
Visual Studio 2015
*/

#include <stdio.h>
int main()
{
	char x; int c;
	printf("Input a character:\n>");
	while (scanf("%c", &x) != EOF)
	{
		if (x >= 97 && x <= 122)
		{
			printf("It's lower case letters!\n");
		}
		else if (x >= 65 && x <= 90)
		{
			printf("It's capital letters!\n");
		}
		else if (x >= 48 && x <= 57)
		{
			printf("It's a number!\n");
		}
		else
		{
			printf("It's a special characters!\n");
		}
		while ((c = getchar()) != '\n'&&c !=EOF );
		printf("Input a character:\n>");
	}
	
	return 0;
}