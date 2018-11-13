#include"fun_header.h"
#define SERVERPORT 9999

int main()
{
	if (false == initIOCPServer(SERVERPORT))
		return -1;
	if (false == createThreads())
		return -1;
	if (false == acceptex())
		return -1;
	while (1)
	{
		int sum = 0;
		for (int i = 0; i < thread_count; i++)
		{
			sum += thread_exit_count[i];
		}
		if (sum == thread_count)
			break;
		else Sleep(1000);
	}
	closeIOCPServer();
	system("pause");
	return 0;
}