#include <stdio.h>
#include<iostream>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int sum=0;
	for (int i = 0; i < argc; i++)
	{
		sum+=atof(argv[i]);
	}
	printf("%d\n", sum);
	system("pause");
	return 0;
}