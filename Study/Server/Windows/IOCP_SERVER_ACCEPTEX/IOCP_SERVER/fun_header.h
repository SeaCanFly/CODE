#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <limits.h>
#include <WinSock2.h>
#include <map>
#include <mswsock.h>
#include <time.h>
#pragma comment(lib,"ws2_32")
LPFN_ACCEPTEX lpfnAcceptEx = 0;					
LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs;
#define BUFSIZE sizeof(Pack)
#define DATASIZE 4096
#define PRE_WSA_SOCKET_COUNT 2000
time_t now;
int thread_count = 0;
HANDLE completion_port = 0;
SOCKET listen_socket = 0;
CRITICAL_SECTION cs;
bool iocp_running = 0;
int thread_exit_count[64] = { 0 };
enum IOType
{
	ACCEPT,
	IO_SEND,
	IO_RECV,
};
#pragma pack(1)
struct Pack
{
	char data[DATASIZE] = { 0 };
};
#pragma pack()
struct CompletionKey
{
	SOCKET client_socket;
	SOCKADDR_IN client_addr;
	char   ip[30] = { 0 };
	bool is_connected = 0;
};
struct ClientManager
{
	std::map<SOCKET, CompletionKey*> client_map;
	int client_count = 0;
}client_manager;
struct OverlappedSock
{
	OVERLAPPED		overlapped;
	SOCKET			client_socket;
	IOType			io_type;
	WSABUF			wsa_buffer;
	char			buffer[BUFSIZE] = { 0 };
};
bool processIO(OverlappedSock* i_os, CompletionKey* i_ck, unsigned long dwTransferred);
void disconnect(CompletionKey* i_client);
bool send(CompletionKey* i_client, const char* buf, int len);
bool recv(CompletionKey* i_client);
void decreaseClientCount();
void increaseClientCount();
void deleteClient(CompletionKey* client);
CompletionKey* createClient(OverlappedSock* i_os,CompletionKey* i_ck);
bool sendCompletion(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred);
bool receiveCompletion(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred);
unsigned int __stdcall workerThread(LPVOID lpParam);
unsigned int __stdcall cmd(LPVOID lpParam);
bool createWsaSocket(SOCKET i_listen_socket);
bool initIOCPServer(int i_server_port);
bool acceptex();
bool createThreads();
bool toParser(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred);
void closeIOCPServer();
bool createWsaSocket(SOCKET i_listen_socket)
{	
	DWORD dwBytes;
	OverlappedSock* pIO;
	pIO = (OverlappedSock*) calloc(1, sizeof(OverlappedSock));	
	pIO->wsa_buffer.buf = pIO->buffer;
	pIO->wsa_buffer.len = BUFSIZE;
	pIO->io_type = ACCEPT;
	pIO->client_socket = WSASocket( AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED );
	
	BOOL rc = lpfnAcceptEx(i_listen_socket, pIO->client_socket,pIO->buffer, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, &dwBytes, &(pIO->overlapped) );
	if( false == rc )
	{
		if( WSAGetLastError() != ERROR_IO_PENDING )
		{
			printf("%d", WSAGetLastError() );
			return false;
		}
	}
	
	return true;
}

bool initIOCPServer(int i_server_port)
{	
	iocp_running = true;
	InitializeCriticalSection(&cs);
	SYSTEM_INFO sysinfo;
	SecureZeroMemory(&sysinfo, sizeof(sysinfo));
	GetSystemInfo(&sysinfo);
	thread_count = sysinfo.dwNumberOfProcessors * 2;
	printf("thread count:%d\n", thread_count);
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
	completion_port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	printf("Completion Port:%p\n", completion_port);
	if (completion_port == 0)
	{
		printf("Completion Port Create Fail!\n");
		return false;
	}

	listen_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listen_socket == 0)
	{
		printf("Socket Create Fail!\n");
		return false;
	}
	CompletionKey* p_completion_key = 0;
	p_completion_key = (CompletionKey*)calloc(1, sizeof(CompletionKey));
	p_completion_key->client_socket = listen_socket;
	CreateIoCompletionPort((HANDLE)listen_socket, completion_port,(ULONG_PTR)p_completion_key, 0);
	

	SOCKADDR_IN serveraddr;
	SecureZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(i_server_port);
	int opt = 1;
	setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(int));
	if (SOCKET_ERROR == bind(listen_socket, (SOCKADDR*)&serveraddr, sizeof(serveraddr)))
	{
		printf("bind Fail!\n");
		return false;
	}
	if (SOCKET_ERROR == listen(listen_socket, SOMAXCONN))
	{
		printf("listen Fail!\n");
		return false;
	}
	printf("listen_port:%d\n",i_server_port);
	return true;
}
bool acceptex()
{
	DWORD dwbytes = 0;
	GUID guidAcceptEx = WSAID_ACCEPTEX;
 
	if( 0 != WSAIoctl( listen_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(guidAcceptEx), &lpfnAcceptEx, sizeof(lpfnAcceptEx), &dwbytes, NULL, NULL) )
	{
	}
	GUID guidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
	if( 0 != WSAIoctl( listen_socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guidGetAcceptExSockaddrs,sizeof(guidGetAcceptExSockaddrs), &lpfnGetAcceptExSockaddrs, sizeof(lpfnGetAcceptExSockaddrs), &dwbytes, NULL, NULL) )  
	{  
	}  
	for (int i = 0; i<PRE_WSA_SOCKET_COUNT; i++)
	{
		createWsaSocket(listen_socket);
	}
	return true;
}
unsigned int __stdcall cmd(LPVOID ipParam)
{
	while (iocp_running)
	{
		char cmd[512] = { 0 };
		scanf("%s", &cmd);
		if (strcmp(cmd, "quit") == 0)
		{
			CloseHandle(completion_port);
			break;
		}
		else if (strcmp(cmd, "count") == 0)
		{
			printf("[connected client count:]%d\n", client_manager.client_count);
			continue;
		}
	}
	return true;
}
bool createThreads()
{
	printf("Start to create work thread..\n");
	for (int i = 0; i < thread_count; ++i)
	{
		unsigned long dwThreadId;
		HANDLE threadHandle = (HANDLE)_beginthreadex(NULL, 0, workerThread, (LPVOID)&thread_exit_count[i], 0, (unsigned int*)&dwThreadId);
		if (threadHandle == INVALID_HANDLE_VALUE)
		{
			printf("Create Thread Fail!\n");
			return false;
		}
		printf("Thread No.%d Created\n", i);
		CloseHandle(threadHandle);
	}	
	unsigned long dwThreadId;
	HANDLE threadHandle = (HANDLE)_beginthreadex(NULL, 0, cmd, 0, 0, (unsigned int*)&dwThreadId);
	CloseHandle(threadHandle);
	return true;
}
unsigned int __stdcall workerThread(LPVOID lpParam)
{
		int* i = (int*)lpParam;
		printf("thread %d[Completion Port:%p] started\n",GetCurrentThreadId(),completion_port);
		while (iocp_running)
		{
			unsigned long dwTransferred=-1;
			OverlappedSock* os = nullptr;
			CompletionKey* ck = nullptr;
			int ret = GetQueuedCompletionStatus(completion_port, &dwTransferred, (PULONG_PTR)&ck,(LPOVERLAPPED*)&os, -1);

			if( !ret )
			{
				DWORD dwIOError = GetLastError();
				if( WAIT_TIMEOUT == dwIOError )
				{
					continue;
				}
				else if( NULL != os )
				{
					CancelIo( (HANDLE)ck->client_socket );	
					disconnect(ck);				
					deleteClient(ck);
				}
				else if(ERROR_INVALID_HANDLE==dwIOError)
				{
					//iocp_running = false;
					*i = 1;
					break;
				}
			}
			else
			{		
				if (os == nullptr)
				{
					printf("Recive Data is zero...Overlapped error\n");
					disconnect(ck);
					deleteClient(ck);
				}
				else if( 0 == dwTransferred && (IO_RECV==os->io_type || IO_SEND==os->io_type))
				{
					printf("Client Disconnected!\n");
					CancelIo( (HANDLE)ck->client_socket );	
					disconnect(ck);		
					deleteClient(ck);				
					free( os );
					os = 0;
					continue;
				}	
				else 
				{
					processIO( os, ck, dwTransferred );
				}
			}
		
		}
	printf("work thread %d exit\n",GetCurrentThreadId());
	return 0;
}
bool processIO(OverlappedSock* i_os, CompletionKey* i_ck,unsigned long dwTransferred)
{
	bool completOK = true;
	if( i_os->io_type == IO_RECV )
	{
		completOK = receiveCompletion(i_ck, i_os, dwTransferred);
	}
	else if( i_os->io_type == IO_SEND )
	{
		completOK = sendCompletion(i_ck, i_os, dwTransferred);
	}
	else if( i_os->io_type == ACCEPT )
	{	

		createClient(i_os, i_ck);
	}
	if (!completOK)
	{
		printf("Completion Error...\n");
		disconnect(i_ck);
		deleteClient(i_ck);
		return false;
	}
	return true;
}
bool toParser(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred)
{
	printf("[%s]", client->ip);
	
	char* temp = ovsock->buffer;
	if (*temp == '/')
		temp++;
	else
		return false;
	if (*temp == 'q')
	{
		memset(ovsock->buffer, 0, DATASIZE);
		memcpy(ovsock->buffer, "q", 1);
		return true;
	}
	else if (*temp == 't')
	{
		temp++;
		char* str = temp;
		while (*temp != '\0')
		{
			printf("%c",*temp++);
		}	
		memcpy(ovsock->buffer, str,temp-str+1);
		return true;
	}
	else if (*temp == 'u')
	{
		int sum = 0,sub = 0;
		temp += 2;
		while (*temp!='\n')
		{
			if (*temp == '\0')
			{
				sum += sub;
				break;
			}
			if (*temp == ' ')
			{
				sum += sub;
				sub = 0;
			}
			if (*temp >= '0'&&*temp <= '9')
			{
				sub *= 10;
				sub +=(int)((*temp)-'0');
			}
			printf("%c", *temp++);	
		}
		printf(" sum=%d\n", sum);
		char str[1024] = { 0 };
		sprintf(str,"sum=%d", sum);	
		memset(ovsock->buffer, 0, DATASIZE);
		memcpy(ovsock->buffer, str,strlen(str));
	}

	return true;
}
bool receiveCompletion(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred)
{
	if (client == nullptr)
	{
		printf("Recive Client is nullptr\n");
		return false;
	}
	if (false == toParser(client, ovsock, dwTransferred))
	{
		free(ovsock);
		ovsock = 0;
		return recv(client);
	}
	bool sendRe = send(client,ovsock->buffer, dwTransferred);
	free(ovsock);
	ovsock = 0;
	if (!sendRe)
	{
		printf("send fail...\n");
	}
	return recv(client);
}
bool recv(CompletionKey* i_client)
{
	if (!i_client->is_connected)
		return false;
	OverlappedSock* recvOV = (OverlappedSock*)calloc(1, sizeof(OverlappedSock));
	recvOV->io_type = IO_RECV;
	recvOV->client_socket = i_client->client_socket;
	unsigned long flags = 0;
	unsigned long recvbytes = 0;
	recvOV->wsa_buffer.buf = recvOV->buffer;
	recvOV->wsa_buffer.len = BUFSIZE;

	if (WSARecv(i_client->client_socket, &recvOV->wsa_buffer, 1, &recvbytes, &flags, (LPWSAOVERLAPPED)recvOV, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("recv error..\n");
			return false;
		}
	}
	printf("Waiting Message...\n");
	return true;
}
bool sendCompletion(CompletionKey* client, OverlappedSock* ovsock, unsigned long dwTransferred)
{
	printf("Message sent\n");
	if (client == nullptr)
	{
		printf_s("SendCompletion client returned nullptr!\n");
		return false;
	}
	if (ovsock->wsa_buffer.len != dwTransferred)
	{
		free(ovsock);
		ovsock = 0;
		return false;
	}
	free(ovsock);
	ovsock = 0;
	return true;
}
bool send(CompletionKey* i_client,const char* buf, int len) 
{
	if (!i_client->is_connected)
		return false;
	OverlappedSock* sendOV = (OverlappedSock*)calloc(1, sizeof(OverlappedSock));
	sendOV->io_type = IO_SEND;
	sendOV->client_socket = i_client->client_socket;
	memcpy_s(sendOV->buffer, BUFSIZE, buf, len);
	unsigned long sendbytes = 0;
	unsigned long flags = 0;
	sendOV->wsa_buffer.buf = sendOV->buffer;
	sendOV->wsa_buffer.len = len;
	if (WSASend(i_client->client_socket,&sendOV->wsa_buffer,1,&sendbytes,flags,(LPWSAOVERLAPPED)&sendOV->overlapped,NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("send error...\n");
			return false;
		}
	}
	printf("\nSending message...\n");
	return true;
}

CompletionKey* createClient(OverlappedSock* i_os,CompletionKey* i_ck)
{
		printf("accept sucess!\n");
		setsockopt( i_os->client_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&(i_ck->client_socket), sizeof(i_ck->client_socket) );


		CompletionKey* client_ck = (CompletionKey*)calloc ( 1, sizeof(CompletionKey) );
		client_ck->client_socket = i_os->client_socket;
		client_ck->is_connected = true;
		SOCKADDR_IN *addrClient = NULL, *addrLocal = NULL;
		int nClientLen = sizeof(SOCKADDR_IN), nLocalLen = sizeof(SOCKADDR_IN);
		u_long arg = 1;
		ioctlsocket(client_ck->client_socket, FIONBIO, &arg);
		int opt = 1;
		setsockopt(client_ck->client_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));
		opt = 0;
		if (SOCKET_ERROR == setsockopt(client_ck->client_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&opt, sizeof(int)))
		{
			printf("SO_RCVBUF change error:%d\n", GetLastError());
			return false;
		}
		lpfnGetAcceptExSockaddrs(i_os->buffer, 0, sizeof(SOCKADDR_IN)+16, sizeof(SOCKADDR_IN)+16, (LPSOCKADDR*)&addrLocal, &nLocalLen,(LPSOCKADDR*)&addrClient, &nClientLen);
 
		sprintf(client_ck->ip, "%s:%d\0",inet_ntoa(addrClient->sin_addr), addrClient->sin_port );
		printf(client_ck->ip );
		CreateIoCompletionPort( (HANDLE)client_ck->client_socket, completion_port, (ULONG_PTR)client_ck, 0 );
	client_manager.client_map.insert(std::pair<SOCKET, CompletionKey*>(i_ck->client_socket,client_ck));
	char on[256] = { 0 };
	time(&now);
	ctime_s(on, sizeof(on), &now);
	printf(",online:%s", on);
	send(client_ck, on, sizeof(on));
	printf("create Client\n");
	increaseClientCount();
	recv(client_ck);
	createWsaSocket( listen_socket );	
	return client_ck;
}
void deleteClient(CompletionKey* client)
{
	client_manager.client_map.erase(client->client_socket);
	free(client);
	client = 0;
	printf("client delete\n");
}
void increaseClientCount()
{
	EnterCriticalSection(&cs);
	client_manager.client_count++;
	printf("client count increase..\nnow client count:%d\n",client_manager.client_count);
	LeaveCriticalSection(&cs);
}
void decreaseClientCount()
{
	EnterCriticalSection(&cs);
	client_manager.client_count--;
	printf("client count decrease..\nnow client count:%d\n",client_manager.client_count);
	LeaveCriticalSection(&cs);
}
void disconnect(CompletionKey* i_client)
{
	if (!i_client->is_connected)
		return;
	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;
	if (SOCKET_ERROR == setsockopt(i_client->client_socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{
		printf("linger option error...\n");
	}
	printf("Client Disconnected: IP = [%s]\n", i_client->ip);
	decreaseClientCount();
	closesocket(i_client->client_socket);
	i_client->is_connected = false;
}
void closeIOCPServer()
{
	closesocket(listen_socket);
	//CloseHandle(completion_port);
	DeleteCriticalSection(&cs);
	WSACleanup();
	printf("IOCP Server closed\n");
}
