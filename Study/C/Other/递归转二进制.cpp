#include<stdio.h>
#include<stdlib.h>
int b(int n); 
void b2(int n);
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		b(n);
		printf("\n");
		b2(n);
	}
	return 0;
}
int b(int n)
{
	if(n==0)
	{
		return n%2;
	}
	else
	{
		b(n/2);
		printf("%d",n%2);
	}
}
void b2(int n)
{
	while(n)
	{
		printf("%d",n%2);
		n=n/2;
	}
}
