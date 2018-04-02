/*
	WinSysDir.cpp
	프로그램 설명 
	  : 시스템 디렉토리와 윈도우즈 디렉토리 확인.
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR sysDir[DIR_LEN];
	TCHAR winDir[DIR_LEN];

	// 시스템 디렉토리 정보 추출.
	GetSystemDirectory(sysDir, DIR_LEN);

	// 윈도우즈 디렉토리 정보 추출.
	GetWindowsDirectory(winDir, DIR_LEN);

	_tprintf(_T("System Dir: %s \n"), sysDir);
	_tprintf(_T("Windows Dir: %s \n"), winDir);

	return 0;
}

