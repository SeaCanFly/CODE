#include<iostream>
#include<cstring>
#include<Windows.h>
using namespace std;
#define LINEMAX 80
int main()
{
	int bullet = 0;
	int direction = 0;
	while (1)
	{
		for (int i = 0; i < bullet; i++)
		{
			printf(" ");
		}
		
		if (direction==0)
		{
			printf(">\r");
			bullet++;	
			if (bullet == LINEMAX)
			{
				direction = 1;
			}
		}
		if (direction==1)
		{
			printf("<");
			for (int i = 0; i < (LINEMAX - bullet);i++)
			{
				printf(" ");
			}
			printf("\r");
			bullet--;
			if (bullet == 0)
			{
				direction = 0;
			}
		}
		Sleep(200);
	}
	return 0;
}