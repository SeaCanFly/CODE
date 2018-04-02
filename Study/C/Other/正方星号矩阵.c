#include <stdio.h>
int main()
{
	int x,i,y,t;
	while (scanf("%d", &x) != EOF)
	{
		for(i=1;i<=x;i++)
		{
			t=i;
			while(t)
			{
				for(y=1;y<=i;y++)
				{
					printf("*");
	 			}
	 			printf("\n");
	 			t--;
	 		}
		}
	}
	printf("\n");
	return 0;
}
