/*
	StringEvent2.cpp
	프로그램 설명: manual-reset mode 동기화 적용 사례.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>    /* _beginthreadex, _endthreadex */


unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam); 

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[])
{	
	HANDLE  hThread[2];
	DWORD dwThreadID[2];

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
	
	hThread[0] = (HANDLE)_beginthreadex (
						NULL, 0, 
						OutputThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadID[0]
					);

	hThread[1] = (HANDLE)_beginthreadex (
						NULL, 0, 
						CountThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadID[1]
					);




	if(hThread[0]==0 ||hThread[1]==0) 
	{
		_fputts(_T("Thread creation error \n"), stdout); 
		return -1;
	}	

	_fputts(_T("Insert string: "), stdout); 
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);	// event의 state를 signaled 상태로 변경.

	WaitForMultipleObjects ( 
				2,           // 배열의 길이.
				hThread,     // 핸들의 배열.
				TRUE,        // 모든 핸들이 신호받은 상태로 될 때 리턴.
				INFINITE	 // 무한 대기.
	); 
		
 	CloseHandle(hEvent);	// event 오브젝트 소멸
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

    return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(hEvent, INFINITE); // event가 signaled 상태가 되기를 기다린다.

  _fputts(_T("Output string: "), stdout); 
  _fputts(string, stdout); 

  return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(hEvent, INFINITE); // event가 signaled 상태가 되기를 기다린다.

  _tprintf(_T("Output string length: %d \n"), _tcslen(string)-1); 

  return 0;
}

