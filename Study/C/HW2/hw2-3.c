/*
name:wangyisen
student id:B577046
game software
homework #2_3
visual studio 2015
*/

#include<stdio.h>
#define THISYEAR 2016
#define TODAY 425
int main()
{
	int y, md;	int d2, m2; int d, t = (TODAY % 100) + 31 + 29 + 31; int num, c;
	printf("Please input your year of birth\n>");
	num = scanf("%d", &y);
	while (num == 0)
	{
		while ((c = getchar()) != EOF && c != '\n');
		num = scanf("\n%d", &y);
	}
	do
	{
		printf("Please input your birthday [0000]\n>");
		while ((c = getchar()) != EOF && c != '\n');
		scanf("\n%d", &md);
		d2 = md % 100;
		m2 = md / 100;
		if (m2 > 12 || m2 <= 0) { printf("Not a correct date,please try again\n"); md = 1; continue; }
		if (d2 > 31 || d2 <= 0) { printf("Not a correct date,please try again\n"); md = 1; continue; }
		if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
		{
			switch (m2)
			{
			case 2:if (d2 > 29) { printf("Not a correct date,please try again\n"); md = 1; }
				   else { d = 31; } break;
			}
		}
		else
		{
			switch (m2)
			{
			case 2:if (d2 >= 29) { printf("Not a correct date,please try again\n"); md = 1; }
				   else { d = 31; }break;
			}
		}
		switch (m2)
		{
		case 1:d = 0; break;
		case 3:d = 59; break;
		case 4:if (d2 == 31) { printf("Not a correct date,please try again\n"); md = 1; }
			   else { d = 90; }break;
		case 5:d = 120; break;
		case 6:if (d2 == 31) { printf("Not a correct date,please try again\n"); md = 1; }
			   else { d = 151; }break;
		case 7:d = 181; break;
		case 8:d = 212; break;
		case 9:if (d2 == 31) { printf("Not a correct date,please try again\n"); md = 1; }
			   else { d = 243; }break;
		case 10:d = 273; break;
		case 11:if (d2 == 31) { printf("Not a correct date,please try again\n"); md = 1; }
				else { d = 304; }break;
		case 12:d = 334; break;
		}
	} while (md == 1);

	y = THISYEAR - y;
	d = d + d2;
	if (y < 0) { printf("Hello,Future people,welcome back.\n"); }
	else if (y == 2016 && md == 1225) { printf("Hello,Jesus!\n"); }
	else if (y == 0 && (d + 1) > t) { printf("Hello,Future people,welcome back.\n"); }
	else if (y == 0 && (d + 1) == t) { printf("Baby,Welcome to the world..\n"); }
	else if (y > 0 && d > t) { printf("you are %d years old and %d days, your birthday is %d/%d\n", y - 1, t + 365 - d, m2, d2); }
	else { printf("you are %d years old and %d days, your birthday is %d/%d\n", y, t - (d + 1), m2, d2); }
	return 0;
}