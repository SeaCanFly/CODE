#include <stdio.h>
int c(int n, int m);
int main()
{
	int x;
	printf("input a number\n>");
	while (scanf("%d", &x) != EOF) 
	{
		int i, sum = 0;
		for (i = 0; i <= x; i++) {sum = sum + c(x, i)*c(x, i);}
		printf("%d\n", sum / (x + 1));
	}
	return 0;
}
int c(int n, int m)
{
	if (m == 0)return 1;
	else 
	{
		int i, k1 = 1, t = 1;
		for (i = n; i > (n - m); i--) {k1 = k1*i;}
		int k2 = 1;
		for (i = 1; i <= m; i++) {k2 = k2*i;}
		return k1 / k2;
	}
}
