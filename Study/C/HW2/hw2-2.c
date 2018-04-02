/*
name:wangyisen
student id:B577046
game software
homework #2_2
visual studio 2015
*/

#include <stdio.h>
int main()
{
	int a[4]; int isnum, c;
	printf("input four numbers\n");
	int i;
	for (i = 0; i < 4; i++)
		{
			printf(">");
			isnum = scanf("%d", &a[i]);
			while (isnum == 0)
				{
				getchar();
				isnum = scanf("\n%d", &a[i]);
				}
		}
	for (i = 0; i <= 2; i++)
		{
			if (a[i] >= a[i + 1]) { a[i + 1] = a[i + 1]; }
			else { a[i + 1] = a[i]; }
		}
	printf("min=%d\n", a[3]);
	return 0;
}