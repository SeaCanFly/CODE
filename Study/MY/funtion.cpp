
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define M 5
int binary_find(int a[], int left, int right, int key)
{
	while (left<right)
	{
		int mid = (left + right) / 2;
		if (key == a[mid])
		{
			printf("find\n");
			printf("a[%d]=%d\n", mid, a[mid]);
			return 1;
		}
		else if (key > a[mid])
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	printf("not find\n");
	return 0;
}
void swap(int* p1, int* p2)
{
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}

void array_sort(int a[], int max)
{
	for (int i = 0; i < max; i++)
	{
		for (int j = i; j < max; j++)
		{
			if (a[i] > a[j])
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				/*swap(&a[i], &a[j]);*/
			}
		}
	}
}
void array_swap(int a[],int max)
{
	for (int i = 0; i < max / 2; i++)
	{
		int t = a[i];
		a[i] = a[max - i-1];
		a[max - i-1] = t;
	}
}
void show_array_int(int a[], int max)
{
	for (int i = 0; i < max; i++)
	{
		printf("a[%d]=%d\n", i, a[i]);
	}
	printf("\n");
}
void show_array_char(char a[],int max)							//字符数组比整形数组多一位
{
	int i = 0;
	while(a[i]!=NULL)
	{
		printf("a[%d]=%d\n",i,a[i]);
		i++;
	}
	printf("\n");
}
void odd(int a[], int max)
{
	printf("odd:");
	for (int i = 0; i<M; i++)
	{
		if (a[i] & 1)
		{
			printf("%d ", a[i]);
		}
	}
}
void even(int a[], int max)
{
	printf("even:");
	for (int i = 0; i<M; i++)
	{
		if (!(a[i] & 1))
		{
			printf("%d ", a[i]);
		}
	}
}
int recour_binary(int n)
{
	if (n == 0)
	{
		return n % 2;
	}
	else
	{
		recour_binary(n / 2);
		printf("%d", n % 2);
	}
}
void Palindrome()
{
	char str[20] = { NULL }; char c;
	while (scanf("%s", str) != EOF)
	{
		int i = 0;
		while (str[i] != NULL)
		{
			i++;
		}
		printf("%s=%d\n", str, i);
		int j = 0;
		for (j = 0; j<i / 2; j++)
		{
			if (str[j] != str[i - j - 1])
			{
				printf("not Palindrome\n");
				break;
			}
		}
		if (j == i / 2)
		{
			printf("Is Palindrome\n");
		}
		while ((c = getchar() != '\n'&& c != EOF));
	}
}
void array_LRinput()
{
	int a[M] = { NULL };
		int num = 0, t = M-1;int j = 0;
		for (int i = 0; i<M; i++)
		{
			
			scanf("%d", &num);
			if (!(num&1))
			{
				a[t] = num;
				t--;
			}
			else
			{
				a[j] = num;
				j++;
			}
		}
		for (int i = 0; i<M; i++)
		{
			printf("%d ", a[i]);
		}
}
void rand_array_int()
{
	int a[M] = { NULL }; 
	srand((unsigned int)time(NULL));
	for (int i = 0; i < M; i++)
	{
		a[i] = rand();
		printf("a[%d]=%d\n", i, a[i]);
	}
	printf("\n");
}
int main()
{
	int a[M] = { NULL };
	srand((unsigned int)time(NULL));
	for (int i = 0; i < M; i++)
	{
		a[i] = rand();
		printf("a[%d]=%d\n", i, a[i]);
	}
	printf("\n");
	
	array_sort(a, M);
	show_array_int(a, M);
	binary_find(a, 0, M, 59);
	array_swap(a, M);
	show_array_int(a, M);
	return 0;
}
int fibol(int x)
{
	int n1 = 1, n2 = 0, t; int i;
	for (i = 1; i <= x; i++)
	{
		printf("%d ", n1);
		t = n1;
		n1 = n1 + n2;
		n2 = t;
	}
	printf("\n");
	return t;
}
void daoqushu()
{
	int n = 0; int m, t;
	int x; int y;
	scanf("%d", &x);
	t = x;
	while (t >= 10)
	{
		t = t / 10;
		m = m * 10;
	}
	while (x>0)
	{
		y = x / m;

		printf("%d", y);
		if (x > 10)
		{
			printf("+");
		}
		n = n + y;
		x = x % m;
		m = m / 10;
	}
	printf("=%d\n", n);
}
void qushu()
{
	int n = 0;
	int x; int y;
	scanf("%d", &x);
	for (; x >0;)
	{

		y = x % 10;
		printf("%d", y);
		if (x > 10)
		{
			printf("+");
		}
		n = n + y;
		x = x / 10;
	}
	printf("=%d\n", n);
}