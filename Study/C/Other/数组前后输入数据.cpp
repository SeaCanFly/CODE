#include<stdio.h>
#include<stdint.h>
#define MAX 10
int main()
{
	int a[MAX] = { NULL };
		int num = 0, t = MAX-1;int j = 0;
		for (int i = 0; i<MAX; i++)
		{
			
			scanf("%d", &num);
			if (!(num&1))
			{
				a[t] = num;
				t--;
			}
			else
			{
				a[j] = num;
				j++;
			}
		}
		for (int i = 0; i<MAX; i++)
		{
			printf("%d ", a[i]);
		}
	
	return 0;
}
