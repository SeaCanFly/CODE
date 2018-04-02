#include<stdio.h>
int main()
{
	int n,c,k=0;
	while(scanf("%d",&n)!=EOF)
	{
		while(n>1)
		{
			n=n>>1;
			k=k+1;
		}
		printf("%d\n",k);
		k=0;
		while((c=getchar())!=EOF&&c!='\n');
	}
	return 0;
}
