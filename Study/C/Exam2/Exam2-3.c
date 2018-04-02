/*
Name:WangYiSen
ID:B577046
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int com(int y)
{
	return rand()%2+1;
}
int input()
{
		int num;int x;int c;
		printf("Input a number,1,2 and press 0 to exit\n>");
		while(scanf("%d",&x)!=EOF)
		{
		
			if((x>=0)&&(x<=2))
			{
			return x;
			}	
			else
			{
			printf("Input error,1,2 and press 0 to exit!\n>");
			while((c=getchar())!=EOF&&c!='\n');
			}
		}
	
}
int main()
{
	int p1;int t=time(0);int p2;int a[3]={0};
	srand(t);p2=rand();
	
	while(p1=input())
	{
		p2=com(p2);
		if(p1==p2)
		{
			printf("You win,mine is %d\n",p2);
			a[1]=a[1]+1;
		}
		else{
			printf("You lose,mine is %d\n",p2);
			a[2]=a[2]+1;
		}
		a[0]=a[0]+1;
	}
	printf("You tried %d times and wins %d times, loses %d times\nYour rate is %.2f",a[0],a[1],a[2],(double)a[1]/a[0]);
	return 0;
	
}
