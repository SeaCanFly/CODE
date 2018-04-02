#include<stdio.h>
void for1()
{
	int line, loop, space, i;
	printf("input an number\n>");
	scanf("%d", &line);
	for (i = 1; i <= line; i++)
	{	
		for(space=(i-1);space>0;space--)
		{
			printf(" ");
		}
		for(loop=(line-i+1);loop>=1;loop--)
		{
			printf("*");
		}
		printf("\n");
	}
}
void for2()
{
	int line, loop, space, i;
	printf("input an number\n>");
	scanf("%d", &line);	
	for(i=1;i<=line;i++)
	{
		for(space=i;space>1;space--)
		{
			printf(" ");
		}
		for(loop=2*line-2*i+1;loop>=1;loop--)
		{
			printf("*");
		}
		printf("\n");
	}
}
int main()
{
	for1();
	for2();
	return 0;
}
