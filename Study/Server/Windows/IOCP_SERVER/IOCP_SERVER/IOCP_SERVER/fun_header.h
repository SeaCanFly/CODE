#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <process.h>
#include <limits.h>
#include <WinSock2.h>
#include <map>
#pragma comment(lib,"ws2_32")
#define BUFSIZE sizeof(Pack)
#define DATASIZE 4096
int thread_count = 0;
HANDLE completion_port = 0;
SOCKET listen_socket = 0;
CRITICAL_SECTION cs;
enum IOType
{
	IO_SEND,
	IO_RECV,
};
#pragma pack(1)
struct Pack
{
	char data[DATASIZE] = { 0 };
};
#pragma pack()
struct Client
{
	bool is_connected = 0;
	SOCKET socket;
	SOCKADDR_IN client_addr;
};
struct ClientManager
{
	std::map<SOCKET, Client*> client_map;
	int client_count = 0;
}client_manager;
struct OverlappedSock
{
	OVERLAPPED		overlapped;
	Client*			client_object;
	IOType			io_type;
	WSABUF			wsa_buffer;
	char			buffer[BUFSIZE];
};

void disconnect(Client* i_client);
bool send(Client* i_client, const char* buf, int len);
bool recv(Client* i_client);
bool onConnect(Client*i_client, SOCKADDR_IN* addr);
void decreaseClientCount();
void increaseClientCount();
void deleteClient(Client* client);
Client* createClient(SOCKET sock);
bool sendCompletion(Client* client, OverlappedSock* ovsock, unsigned long dwTransferred);
bool receiveCompletion(Client* client, OverlappedSock* ovsock, unsigned long dwTransferred);
unsigned int __stdcall workerThread(LPVOID lpParam);
bool initIOCPServer(int i_server_port)
{
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
	printf("IOCP Server Init Succesed.listen_port:%d\n",i_server_port);
	return true;
}
bool startIOThread()
{
	printf("Start to create work thread..\n");
	for (int i = 0; i < thread_count; ++i)
	{
		unsigned long dwThreadId;
		HANDLE threadHandle = (HANDLE)_beginthreadex(NULL, 0, workerThread, (LPVOID)&i, 0, (unsigned int*)&dwThreadId);
		if (threadHandle == INVALID_HANDLE_VALUE)
		{
			printf("Create Thread Fail!\n");
			return false;
		}
		printf("Thread No.%d Created\n", i);
		CloseHandle(threadHandle);
	}	
	return true;
}
bool accept()
{
	if (SOCKET_ERROR == listen(listen_socket, SOMAXCONN))
	{
		printf("listen Fail!\n");
		return false;
	}
	while (true)
	{
		SOCKET acceptedSock = accept(listen_socket, NULL, NULL);
		if (acceptedSock == INVALID_SOCKET)
		{
			printf_s("accept: invalid socket\n");
			continue;
		}
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(acceptedSock, (SOCKADDR*)&clientaddr, &addrlen);
		Client* client = createClient(acceptedSock);
		if (false == onConnect(client, &clientaddr))
		{
			disconnect(client);
			deleteClient(client);
		}
	}
	return true;
}
unsigned int __stdcall workerThread(LPVOID lpParam)
{
	printf("thread [Completion Port:%p] started\n",completion_port);
	while (true)
	{
		unsigned long dwTransferred;
		OverlappedSock* OvSock = nullptr;
		Client* Client = nullptr;
		int ret = GetQueuedCompletionStatus(completion_port, &dwTransferred, (PULONG_PTR)&Client,(LPOVERLAPPED*)&OvSock, -1);
		if (ret == 0 && GetLastError() == WAIT_TIMEOUT)
		{
			printf("Thread Time Out\n");
			continue;
		}
		if (ret == 0 || dwTransferred == 0)
		{
			printf("Recive Data is zero...\n");
			disconnect(Client);
			deleteClient(Client);
			continue;
		}
		if (OvSock == nullptr)
		{
			printf("Recive Data is zero...Overlapped error\n");
			disconnect(Client);
			deleteClient(Client);
		}
		bool completOK = true;
		switch (OvSock->io_type)
		{
		case IO_SEND:
			completOK = sendCompletion(Client, OvSock, dwTransferred);
			break;

		case IO_RECV:
			completOK = receiveCompletion(Client, OvSock, dwTransferred);
			break;
		default:
			printf("IO type Fail : %d\n", OvSock->io_type);
			break;
		}
		if (!completOK)
		{
			printf("Completion Error...\n");
			disconnect(Client);
			deleteClient(Client);
		}
	}
	return 0;
}
bool toParser(Client* client, OverlappedSock* ovsock, unsigned long dwTransferred)
{
	printf("[%s:%d]", inet_ntoa(client->client_addr.sin_addr), ntohs(client->client_addr.sin_port));
	
	char* temp = ovsock->buffer;
	if (*temp == '/')
		temp++;
	else
		return false;
	if (*temp == 'q')
	{
		memset(ovsock->buffer, 0, DATASIZE);
		memcpy(ovsock->buffer, "q", 1);
	}
	if (*temp == 't')
	{
		temp++;
		char* str = temp;
		while (*temp != '\0')
		{
			printf("%c",*temp++);
		}	
		memcpy(ovsock->buffer, str,temp-str);
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
bool receiveCompletion(Client* client, OverlappedSock* ovsock, unsigned long dwTransferred)
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
bool recv(Client* i_client)
{
	if (!i_client->is_connected)
		return false;
	OverlappedSock* recvOV = (OverlappedSock*)calloc(1, sizeof(OverlappedSock));
	recvOV->io_type = IO_RECV;
	recvOV->client_object = i_client;
	unsigned long flags = 0;
	unsigned long recvbytes = 0;
	recvOV->wsa_buffer.buf = recvOV->buffer;
	recvOV->wsa_buffer.len = BUFSIZE;

	if (WSARecv(i_client->socket, &recvOV->wsa_buffer, 1, &recvbytes, &flags, (LPWSAOVERLAPPED)recvOV, NULL) == SOCKET_ERROR)
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
bool sendCompletion(Client* client, OverlappedSock* ovsock, unsigned long dwTransferred)
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
bool send(Client* i_client,const char* buf, int len) 
{
	if (!i_client->is_connected)
		return false;
	OverlappedSock* sendOV = (OverlappedSock*)calloc(1, sizeof(OverlappedSock));
	sendOV->io_type = IO_SEND;
	sendOV->client_object = i_client;
	memcpy_s(sendOV->buffer, BUFSIZE, buf, len);
	unsigned long sendbytes = 0;
	unsigned long flags = 0;
	sendOV->wsa_buffer.buf = sendOV->buffer;
	sendOV->wsa_buffer.len = len;
	if (WSASend(i_client->socket,&sendOV->wsa_buffer,1,&sendbytes,flags,(LPWSAOVERLAPPED)&sendOV->overlapped,NULL) == SOCKET_ERROR)
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

Client* createClient(SOCKET sock)
{
	Client* client = (Client*)calloc(1,sizeof(Client));
	client->socket = sock;
	client->is_connected = false;
	printf("create Client..\n");
	client_manager.client_map.insert(std::pair<SOCKET, Client*>(sock,client));
	return client;
}
bool onConnect(Client*i_client, SOCKADDR_IN* addr)
{
	u_long arg = 1;
	ioctlsocket(i_client->socket, FIONBIO, &arg);
	int opt = 1;
	setsockopt(i_client->socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int));
	opt = 0;
	if (SOCKET_ERROR == setsockopt(i_client->socket, SOL_SOCKET, SO_RCVBUF, (const char*)&opt, sizeof(int)))
	{
		printf("SO_RCVBUF change error:%d\n", GetLastError());
		return false;
	}
	HANDLE handle = CreateIoCompletionPort((HANDLE)i_client->socket, completion_port, (ULONG_PTR)i_client, 0);
	if (handle != completion_port)
	{
		printf("CreateIoCompletionPort error: %d\n", GetLastError());
		return false;
	}
	memcpy(&i_client->client_addr, addr, sizeof(SOCKADDR_IN));
	i_client->is_connected = true;
	printf("Client Connected: IP=[%s:%d]\n", inet_ntoa(i_client->client_addr.sin_addr), ntohs(i_client->client_addr.sin_port));
	increaseClientCount();
	return recv(i_client);
}
void deleteClient(Client* client)
{
	client_manager.client_map.erase(client->socket);
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
void disconnect(Client* i_client)
{
	if (!i_client->is_connected)
		return;
	LINGER lingerOption;
	lingerOption.l_onoff = 1;
	lingerOption.l_linger = 0;
	if (SOCKET_ERROR == setsockopt(i_client->socket, SOL_SOCKET, SO_LINGER, (char*)&lingerOption, sizeof(LINGER)))
	{
		printf("linger option error...\n");
	}
	printf("Client Disconnected: IP = [%s:%d]\n", inet_ntoa(i_client->client_addr.sin_addr), ntohs(i_client->client_addr.sin_port));
	decreaseClientCount();
	closesocket(i_client->socket);
	i_client->is_connected = false;
}
void closeIOCPServer()
{
	CloseHandle(completion_port);
	DeleteCriticalSection(&cs);
	WSACleanup();
	printf("IOCP Server closed\n");
}
