/*
	StringEvent.cpp
	���α׷� ����: 1. ������/�Һ��� ���� ����
	               2. ����ȭ event�� ���� ����.
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

	hEvent = CreateEvent(	// event object ����.
				NULL,		// ��� �Ұ�.
				TRUE,		// manual-reset mode�� ����.
				FALSE,		// non-signaled ���·� ����.
				NULL		// �̸� ���� event.
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

	SetEvent(hEvent);	// event�� state�� signaled ���·� ����.

	WaitForSingleObject(hThread, INFINITE);
		
 	CloseHandle(hEvent);	// event ������Ʈ �Ҹ�
	CloseHandle(hThread);

    return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(hEvent, INFINITE); // event�� signaled ���°� �Ǳ⸦ ��ٸ���.

  _fputts(_T("output string: "), stdout); 
  _fputts(string, stdout); 

  return 0;
}

