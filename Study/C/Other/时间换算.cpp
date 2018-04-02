#include<stdio.h>
int main()
{
	int sec;
	while(scanf("%d",&sec)!=EOF)
	{
		printf("%d:",sec/3600);
		sec=sec%3600;
		printf("%d:",sec/60);
		sec=sec%60;
		printf("%d\n",sec);
	}
	return 0;
}
