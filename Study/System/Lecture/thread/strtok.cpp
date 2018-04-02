/*
    strtok.cpp
    프로그램 설명: 문자열을 토큰으로 나누는 예제.
*/
#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR string[] = 
		_T("Hey, get a life!")
		_T("You don't even have two pennies to rub together.");  // 분리할 문자열.

	TCHAR seps[]   = _T(" ,.!");       // 공백 ',' '\n'을 분리의 대상으로 선택.

    // 토큰 분리 조건, 문자열 설정 및 첫 번째 토큰 반환.
	TCHAR * token = _tcstok( string, seps );
	
	// 계속해서 토큰을 반환 및 출력.
	while( token != NULL )
	{
		_tprintf( _T(" %s\n"), token );
		token = _tcstok( NULL, seps );
	}
    return 0;
}
