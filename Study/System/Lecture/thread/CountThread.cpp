/*
	CountThread.cpp
	프로그램 설명: 생성 가능한 쓰레드의 개수 측정.
*/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define MAX_THREADS (1024*10)

DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD threadNum = (DWORD) lpParam;

	while(1)
	{
		_tprintf(_T("thread num: %d \n"), threadNum);
		Sleep(5000);
	}

    return 0; 
} 

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadId[MAX_THREADS];
    HANDLE hThread[MAX_THREADS];

    // 생성 가능한 최대 개수의 쓰레드 생성

    while(1)
    {

        hThread[cntOfThread] = 
			CreateThread ( 
				NULL,					   // 디폴트 보안 관리자.
				0,				           // 디폴트 스택 사이즈.
				ThreadProc,				   // 쓰레드 main 함수(쓰레드 함수) 설정.
				(LPVOID)cntOfThread,       // 쓰레드 함수의 전달인자.
				0,						   // 디폴트 쓰레드 생성 속성.
				&dwThreadId[cntOfThread]   // 쓰레드 ID 저장을 위한 주소값 전달.
		    );			                
 
        // 쓰레드 생성 확인
        if (hThread[cntOfThread] == NULL) 
        {
			_tprintf(_T("MAXIMUM THREAD SIZE: %d \n"), cntOfThread);
			break;
        }

		cntOfThread++;
    }

    for(DWORD i=0; i<cntOfThread; i++)
    {
        CloseHandle(hThread[i]);
    }

	return 0;
}

