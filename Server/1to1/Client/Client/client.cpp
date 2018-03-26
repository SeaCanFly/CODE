//#define _WIN32_WINNT=0x0501
#include<WinSock2.h>
#include<stdio.h>
#include<iostream>
#include<process.h>
//#include<Windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
struct Csock
{
	SOCKET	client_socket;
	sockaddr_in server_addr;
	char send_buffer[256] = { 0 };
};
unsigned int __stdcall recvMsg(void* p)
{
	int r_ret = -1;	char recv_buffer[256] = { 0 };
	Csock* r = (Csock*)p;
	while (1)
	{
		r_ret = recv(r->client_socket, recv_buffer, sizeof(recv_buffer), 0);
		if (r_ret == 0)continue;
		if (r_ret == SOCKET_ERROR)
		{
			printf("recv error\n");
			return -1;
		}
		recv_buffer[r_ret] = '\0';
		if (strcmp(recv_buffer, "quit") == 0)return 0;
		printf("\n[server:]%s\n[me:]>", recv_buffer);
	}

}
unsigned int __stdcall sendMsg(void* p)
{
	int s_ret;
	char send_buffer[256] = { 0 };
	Csock* s = (Csock*)p;
	while (1)
	{
		printf("[me:]>");
		scanf("%s", send_buffer);
		s_ret=send(s->client_socket, send_buffer, strlen(send_buffer), 0);
		if (s_ret == SOCKET_ERROR)
		{
			printf("send error\n");
			return -1;
		}
	}
}
int main()
{
	WSADATA wsa;
	Csock c;
	char ip[256] = { 0 };
	HANDLE rs[2] = { nullptr };
	int ret = -1, s_ret = -1;
	int server_port = 7777;
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
	printf("IP:");
	scanf("%s", ip);
	c.server_addr.sin_addr.S_un.S_addr = inet_addr(ip);
	c.server_addr.sin_family = AF_INET;
	c.server_addr.sin_port = htons(server_port);
	if (connect(c.client_socket, (sockaddr*)&c.server_addr, sizeof(c.server_addr)) == SOCKET_ERROR)
	{
		printf("connect error\n");
	}
	rs[0] = (HANDLE)_beginthreadex(0, 0, recvMsg, (void*)&c, 0, 0);
	rs[1] = (HANDLE)_beginthreadex(0, 0, sendMsg, (void*)&c, 0, 0);
	WaitForMultipleObjects(2, rs, 1, INFINITE);
	closesocket(c.client_socket);
	CloseHandle(rs[0]);
	CloseHandle(rs[1]);
	WSACleanup();
	system("pause");
	return 0;
}