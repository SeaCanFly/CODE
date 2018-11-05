#include"fun_header.h"
#define SERVERPORT 9999

int main()
{
	if (false == initIOCPServer(SERVERPORT))
		return -1;
	if (false == startIOThread())
		return -1;
	if (false == acceptex())
		return -1;
	while (iocp_running)Sleep(1000);
	closeIOCPServer();
	return 0;
}