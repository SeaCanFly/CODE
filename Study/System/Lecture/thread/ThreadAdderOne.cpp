/*
	ThreadAdderOne.cpp
	프로그램 설명: 프로세스 유사형태 쓰레드 생성.
*/

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

DWORD WINAPI ThreadProc( LPVOID lpParam ) 
{ 
	DWORD * nPtr = (DWORD *) lpParam;

	DWORD numOne = *nPtr;
	DWORD numTwo = *(nPtr+1);

	DWORD total = 0;

	for(DWORD i=numOne; i<=numTwo; i++)
	{
		total += i;
	}

    return total; 
}


int _tmain(int argc, TCHAR* argv[])
{
    DWORD dwThreadID[3];
    HANDLE hThread[3];

	DWORD paramThread[] = {1, 3, 4, 7, 8, 10};
	DWORD total = 0;
	DWORD result = 0;

    hThread[0] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[0]),
				0, &dwThreadID[0]
		    );			                
 
    hThread[1] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[2]),
				0, &dwThreadID[1]
		    );			                
 
    hThread[2] = 
		CreateThread ( 
				NULL, 0,
				ThreadProc,
				(LPVOID)(&paramThread[4]),
				0, &dwThreadID[2]
		    );
 

	if(hThread[0] == NULL || hThread[1] == NULL || hThread[2] == NULL)
	{
		_tprintf(_T("Thread creation fault! \n"));
		return -1;
	}

	WaitForMultipleObjects(3, hThread, TRUE, INFINITE);

	GetExitCodeThread(hThread[0] , &result);
	total += result;

	GetExitCodeThread(hThread[1] , &result);
	total += result;

	GetExitCodeThread(hThread[2] , &result);
	total += result;

	_tprintf(_T("total (1 ~ 10): %d \n"), total);

    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);
    CloseHandle(hThread[2]);

	return 0;
}

