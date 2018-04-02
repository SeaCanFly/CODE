#include<stdio.h>
int a(int n)
{
	if(n==0)
	{
		return 1;
	}
	else
	{
		return 2*a(n-1);
	}
}
int main()
{
	int n,x;
	while(scanf("%d",&n)!=EOF)
	{
		x=a(n);
		printf("%d\n",x);
	}
	return 0;
}

