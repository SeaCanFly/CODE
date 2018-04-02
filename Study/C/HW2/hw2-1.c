/*
name:wangyisen
student id:B577046
game software
homework #2_1
visual studio 2015
*/

#include <stdio.h>
int main()
{
	int x; char y[6]; int num;
	do {
		printf("you are sir or madam?\n>");
		scanf("%s", &y);
	} while (!(strcmpi(y, "sir") == 0 || strcmpi(y, "madam") == 0));
	do {
		printf("input time[00-24]\n>");
		num=scanf("%d", &x);
		while (num != 1) { printf("delete:%c\n", getchar()); num = scanf("%d", &x); }
	} while ((x < 0) || (x > 24));
			if ((x >= 4) && (x <= 11))
				{
					if (strcmpi(y, "sir") == 0)
						printf("Good morning,sir\n");
					else
						printf("Good morning,madam\n");
				}
			else if ((x >= 12) && (x <= 17))
				{
					if (strcmpi(y, "sir") == 0)
						printf("Good afternoon,sir\n");
					else
						printf("Good afternoon,madam\n");
				}
			else if ((x >= 18) && (x <= 20))
				{
					if (strcmpi(y, "sir") == 0)
						printf("Good evening,sir\n");
					else
						printf("Good evening,madam\n");
				}
			else if ((x >= 21) || (x <= 3))
				{
					if (strcmpi(y, "sir") == 0)
						printf("Good night,sir\n");
					else
						printf("Good night,madam\n");
				}
	return 0;
}