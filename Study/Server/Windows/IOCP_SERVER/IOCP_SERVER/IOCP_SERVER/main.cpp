#include"fun_header.h"
#define SERVERPORT 9999

int main()
{
	if (false == initIOCPServer(SERVERPORT))
		return -1;
	if (false == startIOThread())
		return -1;
	if (false == accept())
		return -1;
	closeIOCPServer();
	return 0;
}