/*
    strtok.cpp
    ���α׷� ����: ���ڿ��� ��ū���� ������ ����.
*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR string[] = 
		_T("Hey, get a life!")
		_T("You don't even have two pennies to rub together.");  // �и��� ���ڿ�.

	TCHAR seps[]   = _T(" ,.!");       // ���� ',' '\n'�� �и��� ������� ����.

    // ��ū �и� ����, ���ڿ� ���� �� ù ��° ��ū ��ȯ.
	TCHAR * token = _tcstok( string, seps );
	
	// ����ؼ� ��ū�� ��ȯ �� ���.
	while( token != NULL )
	{
		_tprintf( _T(" %s\n"), token );
		token = _tcstok( NULL, seps );
	}
    return 0;
}
