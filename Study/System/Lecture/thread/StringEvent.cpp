/*
	StringEvent.cpp
	프로그램 설명: 1. 생산자/소비자 모델의 이해
	               2. 동기화 event에 대한 이해.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>    /* _beginthreadex, _endthreadex */


unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{	
	HANDLE  hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(	// event object 생성.
				NULL,		// 상속 불가.
				TRUE,		// manual-reset mode로 생성.
				FALSE,		// non-signaled 상태로 생성.
				NULL		// 이름 없는 event.
			 );	
	if(hEvent==NULL){
		_fputts(_T("Event object creation error \n"), stdout); 
		return -1;
	}
	
	hThread = (HANDLE)_beginthreadex (
						NULL, 0, 
						OutputThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadID
					);

	if(hThread==0) {
		_fputts(_T("Thread creation error \n"), stdout); 
		return -1;
	}	

	_fputts(_T("Insert string: "), stdout); 
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);	// event의 state를 signaled 상태로 변경.

	WaitForSingleObject(hThread, INFINITE);
		
 	CloseHandle(hEvent);	// event 오브젝트 소멸
	CloseHandle(hThread);

    return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(hEvent, INFINITE); // event가 signaled 상태가 되기를 기다린다.

  _fputts(_T("output string: "), stdout); 
  _fputts(string, stdout); 

  return 0;
}

