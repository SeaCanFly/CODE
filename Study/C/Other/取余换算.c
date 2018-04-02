#include<stdio.h>
#include <stdlib.h>
void huansuan()
{
	int x;
	printf("input an number>9\n>");
	scanf("%d",&x);
	printf("50=%d\n",x/50);
	x=x%50;
	printf("10=%d\n",x/10);
	x=x%10;
	printf("5=%d\n",x/5);
	x=x%5;
	printf("1=%d\n",x);
 } 
int  main()
{
	huansuan();
	int x,a,b,c,d,m;
	printf("input an int number\n>");
	scanf("%d",&x);
	a=x/50;
	m=x%50;
	b=m/10;
	c=(m%10)/5;
	d=(m%10)%5;
	printf("%d include 50=%d,10=%d,5=%d,1=%d",x,a,b,c,d);
	
	return 0;
}
