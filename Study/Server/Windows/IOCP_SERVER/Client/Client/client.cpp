
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<process.h>
#include<time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
time_t now;
#define DATASIZE 4096
int quit = 0;
unsigned int t=0;
HANDLE rs[2] = { nullptr };
struct Csock
{
	SOCKET	client_socket;
	sockaddr_in server_addr;
};
unsigned int __stdcall recvMsg(void* p)
{
	int r_ret = 0;	
	char recv_buffer[DATASIZE] = { 0 };
	Csock* r = (Csock*)p;	
	//SOCKADDR_IN peeraddr;
	//int addrlen;
	//addrlen = sizeof(peeraddr);
	while (!quit)
	{
		//r_ret = recvfrom(r->client_socket, recv_buffer, sizeof(recv_buffer), 0, (SOCKADDR *)&peeraddr, &addrlen);
		r_ret = recv(r->client_socket, recv_buffer, DATASIZE, 0);
		if (r_ret == 0)break;
		if (r_ret == SOCKET_ERROR)
		{
			printf("recv error\n");
			break;;
		}
		if (strcmp(recv_buffer, "q") == 0)
		{
			quit = 1;
			printf("\r[server:]disconnected\n[me:]>");
			printf("Press any key to quit\n");
			break;
		}
		printf("\r[server:]%s\n[me:]>", recv_buffer);
	}
	return 0;
}
unsigned int __stdcall sendMsg(void* p)
{
	int s_ret = 0; 
	char send_buffer[DATASIZE] = { 0 };
	Csock* s = (Csock*)p;
	while (!quit)
	{
		printf("[me:]>");
		gets_s(send_buffer,DATASIZE);
		s_ret=send(s->client_socket, send_buffer, DATASIZE, 0);
		if (s_ret == 0)break;
		if (s_ret == SOCKET_ERROR)
		{
			printf("send error\n");
			break;
		}
	}
	printf("disconnected\n");
	return 0;
}
int main()
{
	WSADATA wsa;
	Csock c;
	//Csock udp;
	char ip[256] = { 0 };
	
	
	int ret = -1, s_ret = -1;
	int server_port = 9999;
	int opt = 1;	
	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0)
	{
		printf("WSAstartup error\n");
		return -1;
	}
	c.client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (c.client_socket == INVALID_SOCKET)
	{
		printf("client_socket create error\n");
		WSACleanup();
	}
	//printf("IP:");
	//scanf("%s", ip);
	c.server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	c.server_addr.sin_family = AF_INET;
	c.server_addr.sin_port = htons(server_port);

	/*udp.client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp.client_socket == INVALID_SOCKET)
	{
		printf("udp socket create failed");
		return -1;
	}
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(7000);
	setsockopt(udp.client_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(int));
	ret = bind(udp.client_socket, (SOCKADDR *)&localaddr, sizeof(localaddr));
	if (ret == SOCKET_ERROR)
	{
		printf("udp bind failed\n");
	}*/
	if (connect(c.client_socket, (sockaddr*)&c.server_addr, sizeof(c.server_addr)) == SOCKET_ERROR)
	{
		printf("connect error\n");
	}
	rs[0] = (HANDLE)_beginthreadex(0, 0, recvMsg, (void*)&c, 0, 0);
	rs[1] = (HANDLE)_beginthreadex(0, 0, sendMsg, (void*)&c, 0, &t);
	WaitForMultipleObjects(2, rs, 1, INFINITE);
	closesocket(c.client_socket);
	CloseHandle(rs[0]);
	CloseHandle(rs[1]);
	WSACleanup();
	system("pause");
	return 0;
}