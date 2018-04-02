/*
	PeriodicTimer.cpp
	프로그램 설명: 주기적 타이머에 대한 이해.
*/

#define _WIN32_WINNT	0x0400

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int _tmain(int argc, TCHAR* argv[])
{
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;

    liDueTime.QuadPart=-100000000;

    hTimer = CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));
    if (!hTimer)
    {
        _tprintf( _T("CreateWaitableTimer failed (%d)\n"), GetLastError());
        return 1;
    }

    _tprintf( _T("Waiting for 10 seconds...\n"));

    SetWaitableTimer(hTimer, &liDueTime, 5000, NULL, NULL, FALSE);

   	while(1)
	  {
		    WaitForSingleObject(hTimer, INFINITE);
		    _tprintf( _T("Timer was signaled.\n") );
		    MessageBeep(MB_ICONEXCLAMATION);
	  }
    return 0;
}
