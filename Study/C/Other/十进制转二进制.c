
#include <stdio.h>
int main()
{
	int x,t;
	printf("Input a decimal integer:\n>");
	while (scanf("%d", &x) != EOF)
	{
		int i = 0; int a[30] = { 0 };
		while (x)
		{
			a[i] = x % 2;
			x = x / 2;
			i++;
		}
		printf("x of the binary is ");
		for (i=i-1; i >= 0; i--)
		{
			printf("%d", a[i]);
		}
		printf("\n");
		printf("Input a decimal integer:\n>");
	}
	return 0;
}
