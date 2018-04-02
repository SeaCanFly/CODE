#include<stdio.h>
#include<Windows.h>
#include<tchar.h>
#include<process.h>
typedef struct T
{
	int* p;
	int n;
}T;
HANDLE mutex;
int a[10] = { 0 };
T a1;
void print(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int add(int* a, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	printf("%d\n", sum);
	return sum;
}
unsigned int __stdcall thread0(void* p)
{
	WaitForSingleObject(mutex, INFINITE);
	printf("tid[%u]:", GetCurrentThreadId());
	T* a = (T*)p;
	print(a->p, a->n);
	ReleaseMutex(mutex);
	return 0;
}
unsigned int __stdcall thread1(void* p)
{
	WaitForSingleObject(mutex, INFINITE);
	printf("tid[%u]:", GetCurrentThreadId());
	T* a = (T*)p;
	add(a->p, a->n);
	ReleaseMutex(mutex);
	return 0;
}

unsigned int(__stdcall *thread[2])(void*) = { thread0,thread1 };
int main()
{
	unsigned long int tid[3];
	HANDLE htd[3];

	mutex = CreateMutex(0, 0, 0);
	printf("tid[%u]:", GetCurrentThreadId());
	printf("input 10 numbers:");
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &a[i]);
	}
	a1.p = &a[0];
	a1.n = 10;
	for (int i = 0; i < 2; i++)
	{
		if ((htd[i] = (HANDLE)_beginthreadex(0, 0, thread[i], (void*)&a1, 0, (unsigned*)&tid[i])) == 0)
		{
			printf("create error\n");
		}
	}
	WaitForMultipleObjects(2, htd, 1, INFINITE);
	for (int i = 0; i < 2; i++)
	{
		CloseHandle(htd[i]);
	}
	CloseHandle(mutex);
	return 0;
}