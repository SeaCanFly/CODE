#include<stdio.h>
#include<Windows.h>
#include<tchar.h>
int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb=sizeof(si);
	memset(&si,0,sizeof(si));
	/*TCHAR dir[MAX_PATH+1];
	SetCurrentDirectory(_T("C:/Windows"));
	GetCurrentDirectory(MAX_PATH + 1,dir);*/
	int a[10]={0};TCHAR cmd[500]={0};int i=0;
	for ( i; i < 10; i++)
	{
		scanf(" %d ",&a[i]);
		
	}
	printf("%d\n",i);
	_stprintf(cmd,_T("add1.exe %d %d %d %d %d %d %d %d %d %d"),a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9]);
	if (CreateProcess(0, cmd, 0, 0, 1, CREATE_NEW_CONSOLE, 0, 0, &si, &pi))
	{
		printf("ok\n");
	}
	else
	{
		printf("false\n");
	}

	CloseHandle(&pi);
	return 0;
}
