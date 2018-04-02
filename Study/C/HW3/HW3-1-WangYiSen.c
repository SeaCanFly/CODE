/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_1
Visual Studio 2015
*/

#include <stdio.h>
int fibo1(int x)
{
	int n1 = 1, n2 = 0, t; int i;
	for (i = 1; i <= x; i++)
	{
		printf("%d ", n1);
		t = n1;
		n1 = n1 + n2;
		n2 = t;
	}
	printf("\n");
	return t;
}
int fibo2(int x)
{
	int f1 = 1, f2 = 0; int i;
	for (i = 0; i <= (x/2); i++)
	{	
		f1 = f1 + f2;
		f2 = f1 + f2;
		if ((x & 1) && ((2*i+1) == x))
		{
			printf("%d ", f1); 
			printf("\n");
			return f1;
		}
		else if((i+1)<=(x/2))
		{
			printf("%d ", f1);
			printf("%d ", f2); 
		}
	}
	printf("\n");
	return f2-f1;
}
int fibo_recur(int x)
{
	int t;
	if (x == 1 || x == 2)
		{ t = 1; }
	else
		{t = fibo_recur(x - 1) + fibo_recur(x - 2);}
		return t;
}
int input()
{
	while (1)
	{
		int x; int i = 1; int c;
		printf("Enter an integer greater than 0\n[Enter 0 to exit]\n>");
		while (scanf("%d", &x) != 1)
		{
			if (i == 1)
			{
				printf(">");
				i = 0;
			}
			while ((c = getchar()) != '\n' && c != EOF)
				{i = 1;}
		}
		if (x >= 0)
			{return x;}
	}
}
int main()
{
	int x; int i = 1;
	while (x = input())
	{
		printf("fibo_iter1:");
		fibo1(x);
		printf("fibo_iter2:");
		fibo2(x);
		printf("fibo_recur:");
		for (i = 1; i <= x; i++)
			{printf("%d ", fibo_recur(i));}
		printf("\n");
	}
	return 0;
}