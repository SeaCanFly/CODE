#include <stdio.h>
#include <stdlib.h>
void he()
{
	int a, b, t,s1,s2;
	a = n % 10;
	n = n / 10;
	b = n % 10;
	s1 = s2 = a + b;
	while ((s1 == s2)&&n)
	{
		n = n / 10;
		a = n % 10;
		s2 = a + b;
		b = a;
	}
	if (n != 0)return 0;
	else return s1;
}
int main()
{
	int x;
	while (scanf("%d", &x) != EOF) 
	{
		printf("%d\n", isprime(x));
	}
	
	printf("input a number\n>");
	while (scanf("%d", &x) != EOF)
	{
		int n1, n2, t;
		n1 = x % 10; 
		n2 = n1;
		if(n1==x)exit;
		else
		{
			x=x/10;
			while (x && (n1 == n2 || t == n2))
			{
				t = n1;
				n1 = x % 10;
				x = x / 10;
				n2 = x % 10;
			}
			if (x != 0)printf("0\n");
			else printf("1\n"); 
		}
	}
	return 0;
}
