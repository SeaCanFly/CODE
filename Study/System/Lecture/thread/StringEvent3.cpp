/*
	StringEvent3.cpp
	���α׷� ����: event, mutex ���� ��� ���.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>    /* _beginthreadex, _endthreadex */


unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);
unsigned int WINAPI CountThreadFunction(LPVOID lpParam); 

typedef struct _SynchString
{
	TCHAR string[100];
	HANDLE hEvent;
	HANDLE hMutex; 
} SynchString;

SynchString gSynString;

int _tmain(int argc, TCHAR* argv[])
{	
	HANDLE  hThreads[2];
	DWORD dwThreadIDs[2];

	gSynString.hEvent = CreateEvent(	
							NULL,		
							TRUE,		
							FALSE,		
							NULL		
						);	

	gSynString.hMutex = CreateMutex ( 
							NULL,
							FALSE,
							NULL
						);    

	if(gSynString.hEvent==NULL || gSynString.hMutex==NULL) {
		_fputts(_T("kernel object creation error \n"), stdout); 
		return -1;
	}


	hThreads[0] = (HANDLE)_beginthreadex (
						NULL, 0, 
						OutputThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadIDs[0]
					);

	hThreads[1] = (HANDLE)_beginthreadex (
						NULL, 0, 
						CountThreadFunction, 
						NULL, 0, 
						(unsigned *)&dwThreadIDs[1]
					);


	if(hThreads[0]==0 ||hThreads[1]==0) 
	{
		_fputts(_T("Thread creation error \n"), stdout); 
		return -1;
	}	

	_fputts(_T("Insert string: "), stdout); 
	_fgetts(gSynString.string, 30, stdin);

	SetEvent(gSynString.hEvent);	// event�� state�� signaled ���·� ����.

	WaitForMultipleObjects ( 
				2,           // �迭�� ����.
				hThreads,     // �ڵ��� �迭.
				TRUE,        // ��� �ڵ��� ��ȣ���� ���·� �� �� ����.
				INFINITE	 // ���� ���.
	); 
		
 	CloseHandle(gSynString.hEvent);
 	CloseHandle(gSynString.hMutex);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

    return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(gSynString.hEvent, INFINITE); // event�� signaled ���°� �Ǳ⸦ ��ٸ���.
  WaitForSingleObject(gSynString.hMutex, INFINITE);

  _fputts(_T("Output string: "), stdout); 
  _fputts(gSynString.string, stdout); 

  ReleaseMutex(gSynString.hMutex);

  return 0;
}

unsigned int WINAPI CountThreadFunction(LPVOID lpParam)
{

  WaitForSingleObject(gSynString.hEvent, INFINITE); // event�� signaled ���°� �Ǳ⸦ ��ٸ���.
  WaitForSingleObject(gSynString.hMutex, INFINITE);

  _tprintf(_T("Output string length: %d \n"), _tcslen(gSynString.string)-1); 

  ReleaseMutex(gSynString.hMutex);

  return 0;
}

