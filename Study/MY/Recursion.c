#include <stdio.h>
#include <string.h>
//int POW(int x,int y)
//{
//	if (y == 0)return 1;
//	//else if (y == 1)return 0;
//	else return  (POW(x, y - 1));
//		
//}
//int Pow(int x, unsigned int y)
//{
//	if (y == 0)  return 1;
//	else if (y & 1) { printf("-----%d\n", x); return x * Pow(x, y - 1); }
//	else { 
//		x = Pow(x, y >> 1); 
//	printf("%d\n", x); 
//	return x * x; }
//}
int findstr(const char* s1, const char* s2)
{
	if (s1 == NULL || s2 == NULL)  return 0; 
	int n1 = strlen(s1); int n2 = strlen(s2);
	if (!n1 || !n2)  return 0; 
	const char *psnext = strstr(s1, s2);
	int count = 0;
	if(psnext!=NULL)
	{
		
		psnext += strlen(s2);
		count += (findstr(psnext, s2)+1);
		
	}
	return count;
}
int main()
{ 
	//int x, y;
	//scanf("%d %d", &x, &y);
	//printf("%d\n", sum(x));
	////printf("%d\n", POW(x, y));
	//printf("%d\n", Pow(x, y));
	char a[]= "abc123abc"; char b[] = "abc";

	printf("%d\n", findstr(a, b));

	return 0;
}
//int sum(int x)
//{
//	if (x <= 0)return 0;
//	else return x + sum(x-1);
//}