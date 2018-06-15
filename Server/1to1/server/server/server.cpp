#include<windows.h>
#include<process.h>
#include<iostream>
#include<map>
using namespace std;
#pragma comment(lib,"WS2_32.LIB")
struct SocketPack
{
	int pos;
	SOCKET client_socket;
	sockaddr_in client_addr;
};
map<int,SocketPack*>socket_list;
unsigned int __stdcall recvMsg(LPVOID p)
{
	int r_ret;
	SocketPack* cur_pack = (SocketPack*)p;
	char recv_buffer[256];
	while (1)
	{
		r_ret = recv(cur_pack->client_socket, recv_buffer, sizeof(recv_buffer), 0);
		if (r_ret == 0)continue;
		if (r_ret == SOCKET_ERROR)
		{
			printf("recv from[ip=%s,port=%d] error \n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));
			break;
		}
		recv_buffer[r_ret] = '\0';
		if (strcmp(recv_buffer, "quit") == 0)
		{
			send(cur_pack->client_socket, "quit", 4, 0);
			printf("\n[ip=%s,port=%d] disconnected\n[me:]", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));			
			break;
		}
		printf("\n[client:]%s", recv_buffer);
		printf("[ip=%s,port=%d]\n[me:]>", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));
	}
	socket_list.erase(cur_pack->pos);
	closesocket(cur_pack->client_socket);
	return 0;
}
unsigned int __stdcall sendMsg(LPVOID p)
{
	int s_ret=0;
	char send_buffer[256] = { 0 };
	while (1)
	{
		printf("[me:]>");
		scanf("%s", send_buffer);
		map<int, SocketPack*>::iterator it;
		it = socket_list.begin();
		while(it!=socket_list.end())
		{
			s_ret = send(it->second->client_socket, send_buffer, strlen(send_buffer), 0);
			if (s_ret == SOCKET_ERROR)
			{
				printf("send error %d\n", WSAGetLastError());
				continue;
			}
			it++;
		}
	}
}
int main()
{
	WSADATA wsa;
	SOCKET listen_socket;
	SOCKET client_socket;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	SocketPack cur_socket[100];
	int client_addr_len;
	int listen_port = 7777;
	int ret = -1;
	int i = 0;
	client_addr_len= sizeof(client_addr);
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
		client_socket = accept(listen_socket, (sockaddr*)&client_addr, &client_addr_len);
		
		if (client_socket == INVALID_SOCKET)
		{
			printf("received an invalid socket\n");
			closesocket(listen_socket);
			continue;
		}
		printf("connecting...[ip=%s,port=%d]\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		ret = send(client_socket, "welcome", 7, 0);
		if (ret == SOCKET_ERROR)
		{
			printf("client connection error\n");
			closesocket(client_socket);
			continue;
		}
		cur_socket[i].pos = i;
		cur_socket[i].client_socket = client_socket;
		cur_socket[i].client_addr = client_addr;
		socket_list.insert(pair<int,SocketPack*>(i, &cur_socket[i]));
		HANDLE re = (HANDLE)_beginthreadex(0, 0, recvMsg, (LPVOID)&cur_socket[i], 0, 0);
		HANDLE se = (HANDLE)_beginthreadex(0, 0, sendMsg, 0, 0, 0);
		if (re)CloseHandle(re);
		else
		{
			socket_list.erase(i);
			closesocket(client_socket);
			printf("create recvMsg thread failed\n");
			continue;
		}
		if (se) CloseHandle(se);
		else
		{
			closesocket(client_socket);
			printf("create sendMsg thread failed\n");
			continue;
		}
		i++;
	}

	closesocket(listen_socket);
	WSACleanup();
	system("pause");
	return 0;
}