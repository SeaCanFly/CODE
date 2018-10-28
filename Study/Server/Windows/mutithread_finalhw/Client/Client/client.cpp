//#define _WIN32_WINNT=0x0501
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<stdio.h>
#include<iostream>
#include<process.h>
#include<time.h>
//#include<Windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
time_t now;
bool chat_all = 0;
bool chat_state = 0;
bool u=1;
struct Csock
{
	SOCKET	client_socket;
	sockaddr_in server_addr;
};
struct Pack
{
	int c_type;
	int s_type;
	char id[256] = { 0 };
	char pw[256] = { 0 };
	int x=0;
	int y=0;
	int z=0;
	char chat[512] = { 0 };
	char time[256] = { 0 };
	int online_state = 0;
};
unsigned int __stdcall recvMsg(void* p)
{
	int r_ret = 0;	char recv_buffer[sizeof(Pack)] = { 0 };
	Csock* r = (Csock*)p;
	Pack packet;
	SOCKADDR_IN peeraddr;
	int addrlen;
	addrlen = sizeof(peeraddr);
	while (u)
	{
	//	while (chat_state)
	//	{
			r_ret = recvfrom(r->client_socket, recv_buffer, sizeof(recv_buffer), 0, (SOCKADDR *)&peeraddr, &addrlen);
			if (r_ret == 0)break;
			if (r_ret == SOCKET_ERROR)
			{
				printf("recv error\n");
				break;;
			}
			memcpy(&packet, recv_buffer, sizeof(recv_buffer));
			if (packet.s_type == 2)
			{
				if (chat_state)
				{
					if (chat_all)
						printf("\r[%s:]%s\n[:all]>", packet.id, packet.chat);
					else
						printf("\r[%s:]%s\n[me:]>", packet.id, packet.chat);
				}
			}
			else
			{
				printf("\r[server:]%s\n[me:]>", packet.chat);
			}
	//	}
	}
	return 0;
}
unsigned int __stdcall sendMsg(void* p)
{
	int s_ret = 0; int select = -1; char sub_select[256] = { 0 };
	char send_buffer[sizeof(Pack)] = { 0 };
	char recv_buffer[sizeof(Pack)] = { 0 };
	Csock* s = (Csock*)p;
	Pack packet;
	while (1)
	{
		
		if (select == -1)
		{
			memset(&packet, 0, sizeof(packet));
			printf("-------Welcome-------\n-------Input \"/bye\"to exit-------\n");
			printf("  Input id\n[me:]>");
			scanf("%s", &packet.id);
			if (strcmp(packet.id, "/bye") == 0)
			{
				packet.c_type = -1;
				strcpy(packet.id , "");
				memcpy(send_buffer, &packet, sizeof(packet));
				s_ret = send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				if (s_ret == SOCKET_ERROR)
				{
					printf("send error\n");
					break;;
				}
				printf("disconnect...\n");
				s_ret = recv(s->client_socket, recv_buffer, sizeof(recv_buffer), 0);
				if (s_ret == 0)break;
				if (s_ret == SOCKET_ERROR)
				{
					printf("recv error\n");
					break;;
				}
				memcpy(&packet, recv_buffer, sizeof(recv_buffer));
				if (packet.s_type == -1)
				{
					break;
				}
			}
			printf("  Input password\n[me:]>");
			scanf("%s", &packet.pw);
			if (strcmp(packet.pw, "/bye") == 0)
			{
				packet.c_type = -1;
				strcpy(packet.id, "");
				memcpy(send_buffer, &packet, sizeof(packet));
				s_ret = send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				if (s_ret == SOCKET_ERROR)
				{
					printf("send error\n");
					break;;
				}
				printf("disconnect...\n");
				s_ret = recv(s->client_socket, recv_buffer, sizeof(recv_buffer), 0);
				if (s_ret == 0)break;
				if (s_ret == SOCKET_ERROR)
				{
					printf("recv error\n");
					break;;
				}
				memcpy(&packet, recv_buffer, sizeof(recv_buffer));
				if (packet.s_type == -1)
				{
					break;
				}
			}
			packet.c_type = 0;
			
			memcpy(send_buffer, &packet, sizeof(packet));
			s_ret=send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
			if (s_ret == SOCKET_ERROR)
			{
				printf("send error\n");
				continue;
			}
			printf("login...\n");
			s_ret = recv(s->client_socket, recv_buffer, sizeof(recv_buffer), 0);
			if (s_ret == 0)break;
			if (s_ret == SOCKET_ERROR)
			{
				printf("recv error\n");
				break;;
			}
			memcpy(&packet, recv_buffer, sizeof(recv_buffer));
			if (packet.s_type == 1)
			{
				printf("conneted,now position[%d,%d,%d]\n",packet.x,packet.y,packet.z);
				time(&now);
				char on_time[256] = { 0 };
				ctime_s(on_time, sizeof(on_time), &now);
				strcpy(packet.time, on_time);
				packet.c_type = 3;
				memcpy(send_buffer, &packet, sizeof(packet));
				s_ret = send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				if (s_ret == SOCKET_ERROR)
				{
					printf("send error\n");
					break;;
				}
				select = 0;
				continue;
			}
			else
			{
				printf("Login failed\n");
				continue;
			}
			
			
		}
		if (select == 0)
		{
			printf("-------Press \"/bye\" to exit-------\n-------Press 1 to Control-------\n-------Press 2 to chat-------\n");
			printf("[me:]>");
			scanf("%s", sub_select);
			if (strcmp(sub_select,"/bye") == 0)
			{
				packet.c_type = -1;
				memcpy(send_buffer, &packet, sizeof(packet));
				s_ret=send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				if (s_ret == SOCKET_ERROR)
				{
					printf("send error\n");
					break;;
				}
				printf("disconnect...\n");
				s_ret=recv(s->client_socket, recv_buffer, sizeof(recv_buffer), 0);
				if (s_ret == 0)break;
				if (s_ret == SOCKET_ERROR)
				{
					printf("recv error\n");
					break;;
				}
				memcpy(&packet, recv_buffer, sizeof(recv_buffer));
				if (packet.s_type == -1)
				{
					break;
				}
			}
			if (strcmp(sub_select,"1") == 0)
			{
				printf("input x y z:");
				scanf("%d %d %d", &packet.x, &packet.y, &packet.z);
				packet.c_type = 1;
				memcpy(send_buffer, &packet, sizeof(packet));
				s_ret=send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				if (s_ret == SOCKET_ERROR)
				{
					printf("send error\n");
					break;;
				}
				printf("moving...\n");
				s_ret = recv(s->client_socket, recv_buffer, sizeof(recv_buffer), 0);
				if (s_ret == 0)break;
				if (s_ret == SOCKET_ERROR)
				{
					printf("recv error\n");
					break;;
				}
				memcpy(&packet, recv_buffer, sizeof(recv_buffer));
				printf("now positon:[%d,%d,%d]\n", packet.x, packet.y, packet.z);
				continue;
			}
			if (strcmp(sub_select,"2") == 0)
			{
				chat_all = 1;
				chat_state = 1;
				printf("---------Press \"/out\" to exit chat model---------\n");
				while (1)
				{	
						printf("[:all]>");
						scanf("%s", &packet.chat);
						if (strcmp(packet.chat, "/out") == 0)
						{
							break;
						}
						packet.c_type = 2;
						memcpy(send_buffer, &packet, sizeof(packet));
						send(s->client_socket, send_buffer, sizeof(send_buffer), 0);
				}
				chat_all = 0;
				chat_state = 0;
				continue;

			}

		}
	}
	u = 0;
	printf("disconnected\n");
	return 0;
}
int main()
{
	WSADATA wsa;
	Csock c;
	Csock udp;
	char ip[256] = { 0 };
	HANDLE rs[2] = { nullptr };
	int ret = -1, s_ret = -1;
	int server_port = 7777;
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
	printf("IP:");
	scanf("%s", ip);
	c.server_addr.sin_addr.S_un.S_addr = inet_addr(ip);
	c.server_addr.sin_family = AF_INET;
	c.server_addr.sin_port = htons(server_port);

	udp.client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (udp.client_socket == INVALID_SOCKET)
	{
		printf("udp socket create failed");
		return -1;
	}
	SOCKADDR_IN localaddr;
	ZeroMemory(&localaddr, sizeof(localaddr));
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(9000);
	setsockopt(udp.client_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(int));
	ret = bind(udp.client_socket, (SOCKADDR *)&localaddr, sizeof(localaddr));
	if (ret == SOCKET_ERROR)
	{
		printf("udp bind failed\n");
	}
	if (connect(c.client_socket, (sockaddr*)&c.server_addr, sizeof(c.server_addr)) == SOCKET_ERROR)
	{
		printf("connect error\n");
	}
	rs[0] = (HANDLE)_beginthreadex(0, 0, recvMsg, (void*)&udp, 0, 0);
	rs[1] = (HANDLE)_beginthreadex(0, 0, sendMsg, (void*)&c, 0, 0);
	WaitForMultipleObjects(2, rs, 1, INFINITE);
	closesocket(c.client_socket);
	CloseHandle(rs[0]);
	CloseHandle(rs[1]);
	WSACleanup();
	system("pause");
	return 0;
}