#include <stdio.h>
int Pow(int x, unsigned int y)
{   if(y == 0)  return 1;     
	else if (y & 1) {printf("-----%d\n",x);return x * Pow(x, y-1);   }  
	else{ x = Pow(x, y>>1);printf("%d\n",x);return x * x; }
}
int main()
{
	int a = 2, b = 4;

	printf("%d\n", Pow(2,4));
	return 0;
}
