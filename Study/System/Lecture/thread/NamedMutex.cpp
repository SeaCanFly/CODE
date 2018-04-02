/*
	NamedMutex.cpp
	���α׷� ����: named mutex�� ���� ����.
*/

#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <tchar.h>

  
HANDLE hMutex; 
DWORD dwWaitResult;

void ProcessBaseCriticalSection() 
{
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);

    switch (dwWaitResult) 
    {
        // �����尡 ���ؽ��� �����Ͽ���.
        case WAIT_OBJECT_0:
			_tprintf(_T ("thread got mutex ! \n") );
			break;

        // time-out �߻��Ͽ���.
        case WAIT_TIMEOUT: 
			_tprintf(_T ("timer expired ! \n") );
            return; 

        // ���ؽ� ��ȯ�� ������ �̷����� �ʾҴ�.
        case WAIT_ABANDONED: 
            return; 
    }

	for(DWORD i=0; i<5; i++)
	{
		_tprintf( _T("Thread Running ! \n") );
		Sleep(10000);
	}

	ReleaseMutex(hMutex);
}


int _tmain(int argc, TCHAR* argv[])
{

#if 1
	hMutex = CreateMutex( 
				NULL,                       
				FALSE,                      
				_T("NamedMutex")			
			);								
#else

	hMutex = OpenMutex( 
				MUTEX_ALL_ACCESS,      
				FALSE,                 
				_T("NamedMutex")	   
			 );  

#endif

	if (hMutex == NULL) 
	{
		_tprintf(_T("CreateMutex error: %d\n"), GetLastError());
		return -1;
	}

	ProcessBaseCriticalSection();

	CloseHandle(hMutex);

	return 0;
}


