#include<stdio.h>
#include<stdlib.h>

int main()
{
	char str[20]={NULL};char c;
	while(scanf("%s",str)!=EOF)
	{	int i=0;
		while(str[i]!=NULL)
		{
			i++;
		}
		printf("%s=%d\n",str,i);
		int j=0;
		for(j=0;j<i/2;j++)
		{
			if(str[j]!=str[i-j-1])
			{
				printf("not Palindrome\n");
				break;
			}
		}
		if(j==i/2)
		{
		printf("Is Palindrome\n");
		}
		while((c=getchar()!='\n'&& c!=EOF));
	}
	return 0;
}
