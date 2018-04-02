#include<stdio.h>
void for1()
{
	int line, loop, space, i;
	printf("input an number\n>");
	scanf("%d", &line);
	for (i = 1; i <= line; i++)
		{
			for (space = 1; space <= line - i; space++)
				{
					printf(" ");
				}

			for (loop = 1; loop <= 2 * i - 1; loop++)
				{
					printf("*");
				}
			printf("\n");
		}
}
int main()
{
	char s[10]= {'\0'};
	scanf("%9[^\n]",s);
	char* pstr=s;
	while((*pstr)!=NULL)
		{
			printf("%c",*pstr);
			pstr++;
		}
	printf("\n");

	int a, b;
	int n;
	while((n=scanf("%d%d",&a,&b))!=EOF)
		{
			char c;
			while ((c = getchar()) != '\n'&&c != EOF);
			int t=a+b;
			printf("w:%d,%d,%d\n",a,b,t);
		}
	printf("%d,%d\n",a,b);
	getchar();
}
