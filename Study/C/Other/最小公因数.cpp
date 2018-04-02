#include<stdio.h>
int main()
{
	/*int line, i, loop,space;
	scanf("%d", &line);
	for (i = 1; i <= line; i++)
	{
		for (space = 1; space <= line - i;space++)
		{
			printf(" ");
		}
		for (loop = 1; loop <= 2 * i-1; loop++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (i = 1; i <= line; i++)
	{
		for (space = 1; space <= i; space++)
		{
			printf(" ");
		}
		for (loop = 1; loop <= 2*line-2*i-1; loop++)
		{
			printf("*");
		}
		printf("\n");
	}*/
	int num1, num2,temp;
	scanf("%d %d", &num1, &num2);
	if ((num1&1) || (num2&1))
	{
		 while (num1 != num2)
		{
			if (num1 >= num2)
			{
				temp = num1 - num2;
				num1 = temp;
			}
			else
			{
				temp = num2 - num1;
				num2 = temp;
			}
			
		}
	}
	else
	{
		while (num1 % 2 != 0)
		{
			num1 = num1 >> 1;
		}
		while (num2 % 2 != 0)
		{
			num2 = num2 >> 1;
		}
		while (num1 != num2)
		{
			if (num1 >= num2)
			{
				temp = num1 - num2;
				num1 = temp;
			}
			else
			{
				temp = num2 - num1;
				num2 = temp;
			}
		}
	}
	printf("%d", temp);
	return 0;
}
