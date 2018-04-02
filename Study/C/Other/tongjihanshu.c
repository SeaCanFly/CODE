#include <stdio.h>
#include <math.h>
int main()
{	const int n=4;
	double a[n]; int i; double sum1 = 0.0, sum2 = 0.0;
	for (i = 0; i <=n; i++)
	{
		scanf("%lf", &a[i]);
	}
	for (i = 0; i <=n; i++)
	{
		sum1 = sum1 + a[i];
	}
	double avg = sum1 / 5.0;
	for (i = 0; i <=n; i++)
	{
 		sum2 = sum2 + (a[i] - avg)*(a[i] - avg);
	}
	double u;
	u = sqrt(sum2 / n);
	printf("%lf\n", u);
	return 0;

}
