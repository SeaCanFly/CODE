/*
	CreateProcess.cpp
	프로그램 설명 : 덧셈 프로세스를 생성
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si={0,};
	PROCESS_INFORMATION pi;
	
	si.cb=sizeof(si);
	si.dwFlags=STARTF_USEPOSITION|STARTF_USESIZE;
	si.dwX=100;
	si.dwY=200;
	si.dwXSize=300;
	si.dwYSize=200;
	si.lpTitle=_T("I am a boy!");

	TCHAR command[]=_T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인.
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("C:\\WinSystem"));
	
	GetCurrentDirectory(DIR_LEN, cDir);	//현재 디렉토리 확인.
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);


	state=CreateProcess(NULL,     // 프로세스 생성.
					    command,
						NULL,
						NULL, 
						TRUE, 
						CREATE_NEW_CONSOLE, 
						NULL, 
						NULL, 
						&si, 
						&pi
	);  //CreateProcess
	
	if(state!=0)
		_fputts(_T("Create OK! \n"), stdout);
	else
		_fputts(_T("Create Error! \n"), stdout);

	return 0;
}

