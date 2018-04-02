#include<stdio.h>
#include<stdlib.h>
void odd(int a[], int max);
void even(int a[], int max);
#define MAX 10
int main()
{
	int a[MAX]={NULL};
	for(int i=0;i<MAX;i++)
	{
		a[i]=i+1;
		//scanf("%d",&a[i]);
	}
	odd(a,MAX);
	even(a,MAX);
	return 0;
}
void odd(int a[], int max)
{
	printf("odd:");
	for(int i=0;i<MAX;i++)
	{
		if(a[i]&1)
		{
			printf("%d ",a[i]);
		}
	}
}
void even(int a[], int max)
{
	printf("even:");
	for(int i=0;i<MAX;i++)
	{
		if(!(a[i]&1))
		{
			printf("%d ",a[i]);
		}
	}
}
