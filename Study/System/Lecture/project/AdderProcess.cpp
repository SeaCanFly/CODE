/*
	AdderProcess.cpp
	���α׷� ���� : main �Լ��� �������ڸ� �����ϴ� ���α׷�.
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>


int _tmain(int argc, TCHAR* argv[])
{
	DWORD val1, val2;
	val1=_ttoi(argv[1]);
	val2=_ttoi(argv[2]);

	_tprintf(_T("%d + %d = %d \n"), val1, val2, val1+val2);

	_gettchar(); //���α׷��� ������ ��� ���߱� ����. 
	return 0;
}

