#include<stdio.h>
int main()
{
	int n,i,j,k;
	while(scanf("%d",&n)!=EOF)
	{
		for(i=0;i<=n/500;i++)
		{
			for(j=0;j<=(n-i*500)/700;j++)
			{
				for(k=0;k<=(n-500*i-700*j)/400;k++)
				{
					if(i*500+j*700+k*400==n)
					{
						printf("500:%d,700:%d,400:%d\n",i,j,k);
					}
				}
			}
		}
	}
	return 0;
}
