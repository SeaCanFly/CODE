#include<stdio.h>
#include<math.h>
int main()
{
	int num1,i,j;
	scanf("%d",&num1);
	for(i=2;i<=num1;i++)
	{
		for(j=2;j<i;j++)
			{
				if(i%j==0)
				{
					break;
				}
			}
		if(j==i)
			{
				printf("%d,",i);
			}
	}
	return 0;
 } 
