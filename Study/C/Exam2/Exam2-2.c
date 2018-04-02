/*
Name:WangYiSen
ID:B577046
*/

#include <stdio.h>
int chek(int n)
{
	int t,i=1;int sum=0;int a[100]={0};
	t=n;
	if(n<=0)
		{
			return -1;
		}
	while(t>=10)
		{
			t=t/10;
			i++;
		}
	while(i)
		{
			a[i]=n%10;
			sum=sum+a[i]*a[i]*a[i];
			n=n/10;
			i--;
		}
	return sum;
}
int main()
{
	int x;int che;
	printf("Input a number:\n>");
	while(scanf("%d",&x)!=EOF)
	{
		che=chek(x);
		if(che==x){
			printf("yes, is armstrong\n");
		}
		else if((che!=x)&&(che!=-1))
		{
			printf("NO, not armstrong\n");
		}
		else if(che==-1)
		{
			printf("%d\nInput an integer greater than 0\n",che);
		}
		printf(">");
	}
	return 0;
}
