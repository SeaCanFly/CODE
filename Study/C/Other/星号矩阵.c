#include <stdio.h>
void while1()
{
	int x;
	printf("input an number\n>");
	scanf("%d", &x);
	int i = -x;
	int m = -x;
	while (m <0)
	{
		i=-x;
		while (i<=m)
		{
			printf("*");
			i++;
		}
		printf("\n");
		m++;
	}
}
 void while2()
 {
 	int x,i;
	printf("input an number\n>");
	scanf("%d", &x);
	i = x;
	int m = -x;
	while (m)
	{
		x = i;
		while (-x<=m)
		{
			printf("*");
			x--;
		}
		printf("\n");
		m++;
	}
 }
 void for1()
 {
 		int x, y,i;
	printf("input an number\n>");
	scanf("%d", &x);
	for (y = 1; y <= x; y++)
	{
		for (i = 1; i <= y; i++)
		{ 
			printf("*");
		}
		printf("\n");
	}
 }
 void for2()
 {
 	int line, loop, space, i;
 	printf("input an number\n>");
	scanf("%d", &line);
	for (i = 1; i <= line; i++)
	{
		for (space = 1; space <= line - i; space++)
		{
			printf(" ");
		}

		for (loop = 1; loop <= 2 * i - 1; loop++)
		{
			printf("*");
		}
		printf("\n");
	}
 }
int main()
{
	for1();
	for2();
	while1();
	while2();
	system("pause");

	return 0;
}
