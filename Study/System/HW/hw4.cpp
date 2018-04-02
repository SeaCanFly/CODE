#include<stdio.h>
#include<Windows.h>
#include<tchar.h>
#include<process.h>
typedef struct T
{
	int* p;
	int n;
}T;	
CRITICAL_SECTION cs;
void print(int* a,int n)
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
double avg(int* a, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	double avg = sum / n;
	printf("%f\n", avg);
	return avg;
}
unsigned int __stdcall thread0(void* p)
{
	EnterCriticalSection(&cs);
		printf("tid[%u]:",GetCurrentThreadId());
		T* a = (T*)p;
		print(a->p, a->n);	
	LeaveCriticalSection(&cs);
	return 0;
}	
unsigned int __stdcall thread1(void* p)
{
	EnterCriticalSection(&cs);
	printf("tid[%u]:", GetCurrentThreadId());
		T* a = (T*)p;
		add(a->p, a->n);
	LeaveCriticalSection(&cs);
	return 0;
}
unsigned int __stdcall thread2(void* p)
{
	EnterCriticalSection(&cs);
	printf("tid[%u]:", GetCurrentThreadId());
		T* a = (T*)p;
		avg(a->p, a->n);
	LeaveCriticalSection(&cs);
	return 0;
}
unsigned int(__stdcall *thread[3])(void*) = { thread0,thread1,thread2 };
int main()
{
	unsigned long int tid[3];
	HANDLE htd[3];
	InitializeCriticalSection(&cs);
	int a[10] = { 0 };
	T a1;
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &a[i]);
	}
	a1.p = &a[0];
	a1.n = 10;
	for (int i = 0; i < 3; i++)
	{
	if ((htd[i]=(HANDLE)_beginthreadex(0, 0, thread[i],(void*)&a1,0,(unsigned*)&tid[i])) == 0)
	{
		printf("create error\n");
	}
	}
	WaitForMultipleObjects(3, htd, 1, INFINITE);
	for (int i = 0; i < 3; i++)
	{
		CloseHandle(htd[i]);
	}
	DeleteCriticalSection(&cs);
	return 0;
}