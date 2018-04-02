#include <stdio.h>
int main()
{
	int x, y;
	short n=0;
	scanf("%d %d", &x, &y);
	while (x >= y)
	{
		x = x / y;
		n++;
	}
	printf("%d\n", n);
	return 0;
}
