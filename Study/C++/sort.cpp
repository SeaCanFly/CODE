#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX 100000
template<typename T>
void swap(T* a, T* b)
{
	T t = *a;
	*a = *b;
	*b = t;
}
template<typename T>
void bubbleSort(T* p, int size)
{
	if (!p || size <= 1)return;
	int i = 0;
	int stop = size - 1;
	int temp = stop;
	while (--size)
	{
		i = 0;
		stop = temp;
		//	int flag = 1;
		for (i = 0; i < stop; i++)
		{
			if (p[i] > p[i + 1])
			{
				swap(&p[i], &p[i + 1]);
				temp = i;
				//flag = 0;
			}
		}
		//if (flag)break;
		if (stop == temp)break;
	}
}
template<typename T>
void selectSort(T* p, int num)
{
	int i = 0;
	for (i; i <= num - 2; i++)
	{
		int min = i;
		int j = i + 1;
		for (j; j <= num - 1; j++)
		{
			if (p[j] < p[min])
			{
				min = j;
			}
		}
		swap(&p[i], &p[min]);
	}
}
int bi(int* p, int now, int start, int end)
{
	if (end - start <= 1)
	{
		if (p[now] < p[start])
			return start;
		else if (p[now] > p[end])
			return end;
		else
			return start;
	}
	if (end > start)
	{
		int mid = (start + end) / 2;
		if (p[now] > p[mid])return bi(p, now, mid, end);
		else if (p[now] < p[mid])return bi(p, now, start, mid);
		else if (p[now] == p[mid])return mid;
	}
	else return -1;
}
template<typename T>
void insertSort(T* p, int num)
{
	int i = 1;
	for (i; i < num; i++)
	{
		int temp = p[i];
		int j = i - 1;
		while (j >= 0 && p[j] > temp)
		{
			p[j + 1] = p[j];
			--j;
		}
		//int index=bi(p,i, 0, j);
		//if (temp >= p[index])
		//{
		//		for (j; j > index; j--)
		//		{
		//			p[j + 1] = p[j];
		//		}
		//}
		//else
		//{
		//	for (j; j >= index; j--)
		//	{
		//		p[j + 1] = p[j];
		//	}
		//}
		p[j + 1] = temp;
	}
}
int mid(int arr[], int left, int right)
{
	if (right - left == 1)
	{
		if (arr[left] > arr[right])
		{
			swap(&arr[left], &arr[right]);
		}
		return left;
	}
	else
	{
		int m = (left + right) / 2;
		if (arr[left] > arr[m])
		{
			swap(&arr[left], &arr[m]);
		}
		if (arr[left] > arr[right])
		{
			swap(&arr[left], &arr[right]);
		}
		if (arr[m] > arr[right])
		{
			swap(&arr[m], &arr[right]);
		}
		swap(&arr[m], &arr[left + 1]);
		return left + 1;
	}
}
void quicksort(int arr[], int left, int right)
{
	if (left < right)
	{
		int p = mid(arr, left, right);
		//int p = left;
		int i = left + 2; int j = right-1;
		if (i > right)i = right;
		if (j < left)j = left;
		while (i<=j)
		{
			while (arr[i] < arr[p]&& i<right)i++;
			while (arr[j] > arr[p]&& j>left)j--;
			if (i < j)
			{
				swap(&arr[i], &arr[j]);
			}
			else break;
		}
		swap(&arr[p], &arr[j]);
		quicksort(arr, left, j - 1);
		quicksort(arr, j + 1, right);
	}

}
void quick_sort(int left, int right, int *p) {//这个快排代码可以稳定在100000输入 33s 太慢了。。。
	int i, j, pivot;
	if (left >= right) 
	{
		return;
	}
	//pivot = p[left];                                  //如果不仅性随机交换的话 快排的时间会多出30% 太可怕了
	//p[left] = p[(left + right) / 2];         //
	//p[(left + right) / 2] = pivot;                    //
	i = left;
	j = right;
	pivot = p[i];
	while (i < j)
	{
		while (i < j&&pivot <= p[j]) j--;
		p[i] = p[j];
		while (i < j&&pivot >= p[i]) i++;
		p[j] = p[i];
	}
	p[i] = pivot;
	quick_sort(left, i - 1, p);
	quick_sort(i + 1, right, p);
}
int *split (int *head , int *tail)
{
   int middle = *(head + (tail  -  head) / 2);
   while (1)
   {
       while (*head  <  middle)
            head++;
       tail--;
       while (*tail  >  middle)
            tail--;
       if (head >= tail)
            return head;
       swap (head , tail);
       head++;
   }
}
//快速排序 , 递归调用
void QuickSort(int * first , int *last)           //这个快排太强悍了 1024000输入 耗时0.43s
{
     if (last  >  first+1)
    {
         int *t=split(first, last); //返回中间值所在的位置
         //判断前一段和后一段的长度，  为了提高效率长度小的先操作 ，
         if (last -t < t - first)
         {
              QuickSort(t, last);
              QuickSort(first , t);
         }
         else
         {
              QuickSort(first , t);
              QuickSort(t, last);
         }
    }
}
void heapmax(int a[], int parent, int n)
{
	int child;
	int temp = 0;
	for (temp = a[parent]; 2 * parent + 1 <= n; parent = child)
	{
		child = 2 * parent + 1;
		if ((child != n) && a[child] < a[child + 1])child++;
		if (temp< a[child])a[parent] = a[child];
		else break;
	}
	a[parent] = temp;
}
void buildheap(int a[], int n)
{
	for (int i = n / 2; i >= 0; i--)
	{
		heapmax(a, i, n);
	}
}
void heapsort(int a[], int n)
{
	for (int i = n - 1; i >=1;)
	{
		swap(&a[0], &a[i]);
		heapmax(a, 0, --i);
	}
}
void shellSort(int* a, int n, int* hs,int* he)
{
	int* p = hs;
	while(p<=he)
	{
		int h = *p;
		for (int i=h; i < n; i++)
		{
			int temp = a[i];
			int j = i;
			while (j >= h && a[j - h] > temp)
			{
				a[j] = a[j - h];
				j = j - h;
			}
			a[j] = temp;
		}
		p++;
	}

}
int main()
{
	LARGE_INTEGER t1, t2,t3,t4,t5,t6,t7, tc;
	QueryPerformanceFrequency(&tc);

	srand(unsigned int(time(0)));
	int a[MAX] = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		a[i] = MAX-i;//rand() % 100;
	}
	for (int i = 0; i < MAX; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	int h[3] = { 5,3,1 };
	QueryPerformanceCounter(&t1);
	//bubbleSort(a, MAX);
	//selectSort(a, MAX);
	//insertSort(a, MAX);
	//quicksort(a, 0, MAX-1);
	//quick_sort(0, MAX - 1, a);
	//QuickSort(a, &a[MAX - 1]);
	//buildheap(a, MAX);
	//heapsort(a, MAX);
	shellSort(a, MAX,h,&h[2]);
	QueryPerformanceCounter(&t2);
	for (int i = 0; i < MAX; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\nUse Time:%.10f\n", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
	system("pause");
	return 0;
}