#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define t 0x01 
#define f1 0x02
int main()
{
	int a1 = 1;// b1 = 0x0100;
	char flag = 0x01;
	flag |= f1; //falg = flag | f1;
	char ch=0;
	scanf("%c", &ch);
	if (ch=='a')
	{
		flag &= ~t; //flag=flag & ~t
	}
	if (flag & t)
		printf("flag=true,%x\n", flag);
	else
		printf("flage=flase\n");
}