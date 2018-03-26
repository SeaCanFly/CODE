#include<windows.h>
#include<process.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"WS2_32.LIB")
struct sock
{
	SOCKET client_socket;
	sockaddr_in client_addr;
};
unsigned int __stdcall recvMsg(LPVOID p)
{
	int r_ret;
	sock* r = (sock*)p;
	char recv_buffer[256];
	while (1)
	{
		r_ret = recv(r->client_socket, recv_buffer, sizeof(recv_buffer), 0);
		if (r_ret == 0)continue;
		if (r_ret == SOCKET_ERROR)
		{
			printf("recv from[ip=%s,port=%d] error \n", inet_ntoa(r->client_addr.sin_addr), ntohs(r->client_addr.sin_port));
			return -1;
		}
		recv_buffer[r_ret] = '\0';
		if (strcmp(recv_buffer, "quit") == 0)
		{
			send(r->client_socket, "quit", 4, 0);
			printf("\n[ip=%s,port=%d] disconnected\n[me:]", inet_ntoa(r->client_addr.sin_addr), ntohs(r->client_addr.sin_port));			
			return 0;
		}
		printf("\n[client:]%s", recv_buffer);
		printf("[ip=%s,port=%d]\n[me:]>", inet_ntoa(r->client_addr.sin_addr), ntohs(r->client_addr.sin_port));
	}
	return 0;
}
unsigned int __stdcall sendMsg(LPVOID p)
{
	int s_ret=0;
	sock* sen = (sock*)p;
	char send_buffer[256] = { 0 };
	while (1)
	{
		printf("[me:]>");
		scanf("%s", send_buffer);
		s_ret = send(sen->client_socket, send_buffer, strlen(send_buffer), 0);
		if (s_ret == SOCKET_ERROR)
		{
			printf("send error %d\n",WSAGetLastError());
			return -1;
		}
	}
}
int main()
{
	WSADATA wsa;
	SOCKET listen_socket;
	sockaddr_in server_addr;
	sock s;
	int client_addr_len;
	int listen_port = 7777;
	int ret = -1;
	int i = 0;
	client_addr_len= sizeof(s.client_addr);
	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0)
	{
		printf("WSAstartup error\n");
		WSACleanup();
		return -1;
	}
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET)
	{
		printf("listen_socket creat error\n");
		WSACleanup();
		return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(listen_port);
	if (bind(listen_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("bind error\n");
		closesocket(listen_socket);
		WSACleanup();
		return -1;
	}
	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listening error\n");
		closesocket(listen_socket);
		WSACleanup();
		return -1;
	}
	printf("listening on port=%d\n", listen_port);
	while (1)
	{
		s.client_socket = accept(listen_socket, (sockaddr*)&s.client_addr, &client_addr_len);
		
		if (s.client_socket == INVALID_SOCKET)
		{
			printf("received an invalid socket\n");
			closesocket(listen_socket);
			WSACleanup();
			return -1;
		}
		printf("connecting...[ip=%s,port=%d]\n", inet_ntoa(s.client_addr.sin_addr), s.client_addr.sin_port);
		ret = send(s.client_socket, "welcome", 7, 0);
		if (ret == SOCKET_ERROR)
		{
			printf("client connection error\n");
			closesocket(s.client_socket);
			continue;
		}
		HANDLE re = (HANDLE)_beginthreadex(0, 0, recvMsg, (LPVOID)&s, 0, 0);
		HANDLE se = (HANDLE)_beginthreadex(0, 0, sendMsg, (LPVOID)&s, 0, 0);
		CloseHandle(re);
		CloseHandle(se);
	}

	closesocket(listen_socket);
	WSACleanup();
	system("pause");
	return 0;
}