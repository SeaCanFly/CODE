#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <process.h>
using namespace std;


CRITICAL_SECTION hCriticalSection;
int total = 0;
float Average = 0;
bool Is_total_complete = false;
void input_number(int arr[10])
{
	
	int num_count = 0;
	

	for (; num_count < 10;)
	{

		cout << num_count + 1 << "번째 숫자 입력하세요=> ";
		cin >> arr[num_count];		
		num_count++;			
	}
	cout << "=-=-=숫자입력 끝=-=-=-=-=" << endl;	
}


DWORD WINAPI Thread_addnum(LPVOID lpParam)
{
	int * nPtr = (int *)lpParam;
	EnterCriticalSection(&hCriticalSection);
	int value = 0;
	int test_a = 0;
	for (int i = 0; i<10; i++)
	{
		
		test_a = *(nPtr + i); 
		total += test_a;
	}	
	cout << "합계 끝났다" << endl;
	Is_total_complete = true;
	LeaveCriticalSection(&hCriticalSection);
	return 0; // 정상적 종료.
}
DWORD WINAPI Thread_avenum(LPVOID lpParam)
{
	EnterCriticalSection(&hCriticalSection);
	cout << "평균 차례네" << endl;
	Average = (float)(total / 10.0f);//합계 계산이 완료된 것을 기반으로 평균 계산. 임계영역 설정으로 두 스레드의 연산이 겹칠 우려는 없다.

	LeaveCriticalSection(&hCriticalSection);
	return 0; // 정상적 종료.
}
void resultcaculate(int arr[10])
{
	
	int count = 0;
	int com = 0;
	
	int numarr[30];
	int input_arr[3][11];
	int tmp_sum = 0;
	DWORD dwThreadID[2];
	HANDLE hThread[2];	


	hThread[0] =//합계
		CreateThread(
			NULL, 0,
			Thread_addnum,
			(LPVOID)(arr),
			0, &dwThreadID[0]
		);
	WaitForSingleObject(hThread[0], INFINITE);
	hThread[1] =//평균
		CreateThread(
			NULL, 0,
			Thread_avenum,
			NULL,
			0, &dwThreadID[1]
		);
	


	if (hThread[0] == NULL || hThread[1] == NULL )
	{
		cout << "Thread creation fault! \n";
		
	}

	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);	


	
	cout << "합계는 " << total<< "평균은 " <<Average<< endl;
}
void showNumber(int arr[10])
{
	cout << "숫자 출력" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
}


void main()
{
	InitializeCriticalSection(&hCriticalSection);
	char tmp_ch;
	

	int numberarr[10];
	input_number(numberarr);
	showNumber(numberarr);
	resultcaculate(numberarr);

	cout << "끝났어요. " << endl;
	cin >> tmp_ch;
	DeleteCriticalSection(&hCriticalSection);
}

