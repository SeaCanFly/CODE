#include<stdio.h>
int main()
{
	int i,n1,n2;
	while(scanf("%d %d",&n1,&n2)!=EOF)
	{
		if(n1>n2)
		{
			n2=n2-n1;
			n1=n1+n2;
			n2=n1-n2;
		}
		for(n1;n1<=n2;n1++)
		{
			for(i=1;i<=9;i++)
			{
				printf("%dx%d=%d ",n1,i,n1*i);
			}
			printf("\n");
		}
	
	}
	return 0;
}
	 
 
