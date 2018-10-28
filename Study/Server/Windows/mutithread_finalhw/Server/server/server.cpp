#define  _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<process.h>
#include<iostream>
#include<fstream>
#include<ostream>
#include<map>
#include<time.h>
using namespace std;
#pragma comment(lib,"WS2_32.LIB")
time_t now;
CRITICAL_SECTION cs;
struct SocketPack
{
	char flag[256] = { 0 };
	SOCKET client_socket;
	SOCKET udp;
	sockaddr_in udp_addr;
	sockaddr_in client_addr;
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
map<string,SocketPack*>socket_list;
unsigned int __stdcall recvMsg(LPVOID p)
{
	int r_ret;
	SocketPack* cur_pack = (SocketPack*)p;
	char recv_buffer[sizeof(Pack)] = { 0 };
	char send_buffer[sizeof(Pack)] = { 0 };
	Pack packet;
	while (1)
	{
		memset(&packet, 0, sizeof(packet));
		memset(&recv_buffer, 0, sizeof(recv_buffer));
		r_ret = recv(cur_pack->client_socket, recv_buffer, sizeof(recv_buffer), 0);
		if (r_ret == 0)break;
		if (r_ret == SOCKET_ERROR)
		{
			printf("[ip=%s,port=%d]disconnected\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));
			break;
		}
		memcpy(&packet, recv_buffer, sizeof(recv_buffer));
		if (packet.c_type == -1)
		{
			if (strcmp(packet.id, "") == 0)
			{
				printf("\n[ip=%s,port=%d]disconnection request\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));
				packet.s_type = -1;
				memcpy(send_buffer, &packet, sizeof(packet));
				send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);
				printf("\n[ip=%s,port=%d]disconnection request success\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port));

				break;
			}
			printf("\n[ip=%s,port=%d,user:%s]disconnection request\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);
			packet.s_type = -1;
			packet.online_state = 0;
			memcpy(send_buffer, &packet, sizeof(packet));
			send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);
			printf("\n[ip=%s,port=%d,user:%s]disconnection request success\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);
			sprintf(packet.chat, "[user:%s]disconnected\n", packet.id);
			memcpy(send_buffer, &packet, sizeof(packet));
			sendto(cur_pack->udp, send_buffer, sizeof(send_buffer), 0, (SOCKADDR *)&cur_pack->udp_addr, sizeof(cur_pack->udp_addr));
			break;
		}
		if (packet.c_type==0)
		{
			printf("\n[ip=%s,port=%d,user:%s]connection request\n",inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);
			char path[256] = { 0 };
			sprintf(path, "user/%s_%s.txt", packet.id, packet.pw);
			FILE* user;
		//	FILE* on;
			user = fopen(path, "r");
			if (!user)
			{
				printf("Invalid User\n");
				packet.s_type = 0;
				memcpy(send_buffer, &packet, sizeof(packet));
				send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);
				continue;
			}
		/*	on = fopen("log.txt", "a");
			if (!on)
			{
				printf("log.txt open failed\n");	
				packet.s_type = 0;
				memcpy(send_buffer, &packet, sizeof(packet));
				send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);
				continue;
			}*/
			char data[sizeof(Pack)] = { 0 };
			fgets(data, sizeof(Pack), user);
			sscanf(data, "%d %d %d", &packet.x,&packet.y,&packet.z);
			packet.s_type = 1;
			packet.online_state = 1;
			memcpy(send_buffer, &packet, sizeof(packet));
			send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);			
		//	fclose(on);
			fclose(user);
			printf("\n[ip=%s,port=%d,user:%s]connection request success\n",inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);	
			
		}
		else if (packet.c_type == 1)
		{
			printf("\n[ip=%s,port=%d,user:%s]control request\n",inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);
			char path[256] = { 0 };
			sprintf(path, "user/%s_%s.txt", packet.id, packet.pw);
			FILE* ctl;	
			ctl = fopen(path, "w");
			if (!ctl)
			{
				printf("can't open user.txt\n");
				
				continue;
			}
			char data[sizeof(Pack)] = { 0 };
			sprintf(data, "%d %d %d\n", packet.x, packet.y, packet.z);
			fputs(data, ctl);
			memcpy(send_buffer, &packet, sizeof(packet));
			send(cur_pack->client_socket, send_buffer, sizeof(send_buffer), 0);
			printf("\n[ip=%s,port=%d,user:%s]positon save successed\n", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port), packet.id);
			fclose(ctl);
		}
		else if (packet.c_type == 2)
		{
			printf("\n[ip=%s,port=%d,user:%s]chat request\n",inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);
			packet.s_type = 2;
			memcpy(send_buffer, &packet, sizeof(packet));
			sendto(cur_pack->udp, send_buffer, sizeof(send_buffer), 0, (SOCKADDR *)&cur_pack->udp_addr, sizeof(cur_pack->udp_addr));
			printf("\n[ip=%s,port=%d,user:%s]send to all done\n",inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port),packet.id);

		}
		else if (packet.c_type == 3)
		{
			EnterCriticalSection(&cs);
			FILE* log;
			char str[2048] = { 0 };
			log = fopen("log.txt", "a");
			if (!log)
			{
				printf("file open failed\n");
				return 0;
			}
			sprintf(str, "ip:%s port:%d user:%s[login]%s", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port), packet.id, packet.time);
			printf("\n[ip=%s,port=%d,user:%s]connected,time:%s", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port), packet.id, packet.time);
			fputs(str, log);
			fclose(log);
			LeaveCriticalSection(&cs);
		}
		printf("\n[:all]>");
	}

	

	char off[256] = { 0 };
	time(&now);
	ctime_s(off, sizeof(off), &now);
	EnterCriticalSection(&cs);
	FILE* log;
	log = fopen("log.txt", "a");
	if (!log)
	{
		printf("file open failed\n");
		return 0;
	}
	char off_time[256] = { 0 };
	char str[2048] = { 0 };
	ctime_s(off_time, sizeof(off_time), &now);
	printf("\n[ip=%s,port=%d,user:%s]disconnected,time:%s", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port), packet.id,off_time);
	sprintf(str, "ip:%s port:%d user:%s[offline]%s", inet_ntoa(cur_pack->client_addr.sin_addr), ntohs(cur_pack->client_addr.sin_port), packet.id, off_time);
	fputs(str, log);
	fclose(log);
	LeaveCriticalSection(&cs);	
	socket_list.erase(cur_pack->flag);
	closesocket(cur_pack->client_socket);
	free(cur_pack);
	cur_pack = 0;
	return 0;
}
unsigned int __stdcall sendMsg(LPVOID p)
{
	int s_ret=0;
	SocketPack* udp = (SocketPack*)p;
	char send_buffer[sizeof(Pack)] = { 0 };
	Pack packet;
	while (1)
	{
		printf("[:all]>");
		scanf("%s", packet.chat);
		memcpy(send_buffer, &packet, sizeof(packet));
		s_ret= sendto(udp->udp, send_buffer, sizeof(send_buffer), 0,(SOCKADDR *)&udp->udp_addr, sizeof(udp->udp_addr));
		if (s_ret == SOCKET_ERROR) 
		{
			printf("sendto error\n");
			continue;
		}
	}
	return 0;
}
int main()
{
	WSADATA wsa;
	SOCKET listen_socket;
	SOCKET client_socket;
	SOCKET udp;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	sockaddr_in udp_addr;

	SocketPack u;
	//SocketPack udp;
	int client_addr_len;
	int listen_port = 7777;
	int ret = -1;
	unsigned int i = 0;
	client_addr_len= sizeof(client_addr);
	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0)
	{
		printf("WSAstartup error\n");
		WSACleanup();
		return -1;
	}
	InitializeCriticalSection(&cs);
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_socket == INVALID_SOCKET)
	{
		printf("listen_socket create error\n");
		WSACleanup();
		return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(listen_port);

	udp= socket(AF_INET, SOCK_DGRAM, 0);
	if (udp== INVALID_SOCKET)
	{
		printf("udp create error\n");
		return -1;
	}
	bool bEnable = 1;
	ret = setsockopt(udp, SOL_SOCKET, SO_BROADCAST,(char *)&bEnable, sizeof(bEnable));
	if (ret == SOCKET_ERROR)
	{
		printf("udp setsockopt error\n");
		return -1;
	}
	//SOCKADDR_IN remoteaddr;
	ZeroMemory(&udp_addr, sizeof(udp_addr));
	udp_addr.sin_family = AF_INET;
	udp_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	udp_addr.sin_port = htons(9000);


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
	u.udp = udp;
	u.udp_addr = udp_addr;
	printf("listening on port=%d\n", listen_port);
	
	while (1)
	{
		SocketPack* cur_socket = (SocketPack*)malloc(sizeof(SocketPack));
		client_socket = accept(listen_socket, (sockaddr*)&client_addr, &client_addr_len);
		
		if (client_socket == INVALID_SOCKET)
		{
			printf("received an invalid socket\n");
			closesocket(listen_socket);
			continue;
		}
		printf("\nconnecting...[ip=%s,port=%d]\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		char t_flag[256] = { 0 };
		sprintf(t_flag, "%s_%d", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
		strcpy(cur_socket->flag, t_flag);
		cur_socket->client_socket = client_socket;
		cur_socket->client_addr = client_addr;
		cur_socket->udp = udp;
		cur_socket->udp_addr = udp_addr;
		socket_list.insert(pair<string,SocketPack*>(cur_socket->flag, cur_socket));
		HANDLE re = (HANDLE)_beginthreadex(0, 0, recvMsg, (LPVOID)cur_socket, 0, 0);
		HANDLE se = (HANDLE)_beginthreadex(0, 0, sendMsg, (LPVOID)&u, 0, 0);
		if (re)CloseHandle(re);
		else
		{
			socket_list.erase(cur_socket->flag);
			free(cur_socket);
			cur_socket = 0;
			closesocket(client_socket);
			printf("create recvMsg thread failed\n");
			continue;
		}
		if (se) CloseHandle(se);
		else
		{
			socket_list.erase(cur_socket->flag);
			free(cur_socket);
			cur_socket = 0;
			closesocket(client_socket);
			printf("create sendMsg thread failed\n");
			continue;
		}
	}

	closesocket(listen_socket);
	WSACleanup();
	DeleteCriticalSection(&cs);
	system("pause");
	return 0;
}