/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_4
Visual Studio 2015
*/

#include <stdio.h>
int main()
{
	char word[30] = { '\0' }; char search, check; int c;
	printf("Input a word:\n>");
	while (scanf("%s", word) != EOF)
	{
		while ((c=getchar()) != '\n'&&c!=EOF);
		int i = 0, t = 0;
		printf("Input the letters you want to search for:\n>");
		scanf("%c", &search);
		for (i; i < 30; i++)
		{
			check = word[i];
			if (check == search)
			{
				t++;
			}
		}
		printf("%s,appear %c %d times\n", word, search, t);
		printf("Input a word:\n>");
	}
	return 0;
}