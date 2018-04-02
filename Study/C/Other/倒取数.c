#include <stdio.h>
int main()
{
	int n=0;
	int x; int y;
	scanf("%d", &x);
	for (;x >0;)
	{
		
		y = x % 10;
		printf("%d", y);
		if (x > 10)
		{
			printf("+");
		}
		n = n + y;
		x = x / 10;
	}
	printf("=%d\n", n);
	return 0;
}
