#include <stdio.h>
void daoqushu()//倒取数 
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
}
int main()//正取数 
{
	int n=0;int m,t;
	int x; int y;
	scanf("%d", &x);
	t=x;
	while(t>=10)
	{
		t=t/10;
		m=m*10;
	}
	while (x>0)
	{
		y = x / m;
	
		printf("%d", y);
		if (x > 10)
		{
			printf("+");
		}
		n = n + y;
		x = x % m;
		m = m / 10;
	}
	printf("=%d\n", n);
	return 0;
}
