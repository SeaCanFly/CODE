//
// IOCP�� ���� Ȯ�� API�� �̿��ؼ� ACCEPT �� RECV�� IOCP�� �����Ͽ� �񵿱� ó���� ����.
// ���� ���� �� ������ ���� �ʰ� ACCEPT�� �����ϵ��� ���� Ǯ ó��.
// ���� Ǯ�� ������ ��� ���� ó���� ���� WSAEventSelect API�� ���.
// ���� ������ ���� �뷮 Ŭ���̾�Ʈ ���� ó���� ���� �����ִ� ������ ���� ���� ����.
//
#include "stdafx.h"
#include "Winsock2.h"
#include "Mswsock.h"
#include "set"
#include "iostream"
using namespace std;

#pragma comment(lib, "Ws2_32.lib")


// �񵿱� ������� ���� OVERLAPPED ��� ����ü ����
struct SOCK_ITEM : OVERLAPPED
{
	SOCKET	_sock;
	char	_buff[4096];

	SOCK_ITEM()
	{
		hEvent = NULL;
		Offset = OffsetHigh = 0;
		memset(_buff, 0, sizeof(_buff));
		_sock = INVALID_SOCKET;
	}
	SOCK_ITEM(SOCKET sock)
	{
		hEvent = NULL;
		Offset = OffsetHigh = 0;
		memset(_buff, 0, sizeof(_buff));
		_sock = sock;
	}
};
typedef SOCK_ITEM* PSOCK_ITEM;
// �ڽ� ���� �� ���� Ǯ ������ ���� SET ����
typedef std::set<PSOCK_ITEM>  SOCK_SET;


// ������ Ǯ �����忡 �Ű������� �Ѱ��� ������ ��� �ִ� ����ü
struct IOCP_ENV
{
	CRITICAL_SECTION _cs;
	SOCK_SET		_socks;		// ����� �ڽ� ���� ������ ��
	SOCK_SET		_spool;		// ���� ��� ���� Ǯ ������ ��
	HANDLE			_iocp;		// ICOP �ڵ�
	SOCKET			_listen;	// ���� ����

	IOCP_ENV()
	{
		_iocp   = NULL;
		_listen = INVALID_SOCKET;
		InitializeCriticalSection(&_cs);
	}
	~IOCP_ENV()
	{
		DeleteCriticalSection(&_cs);
	}
};
typedef IOCP_ENV* PIOCP_ENV;

#define SVR_DEF_PORT	9001
#define PERMIT_INC_CNT	50	// ���� Ǯ ��Ʈ�� ���� ��

// IOCP ���� �ĺ� Ű
#define IOCP_KEY_LISTEN	 1	// ���� ���� �ñ׳�
#define IOCP_KEY_CHILD	 2	// �ڽ� ���� �ñ׳�
#define IOCP_KEY_EXIT	 3	// ���� ���� �ñ׳�


// �ܼ� �󿡼��� Ctrl-C Ű ���� ó���� ���� �ڵ鷯
HANDLE g_hevExit = NULL;
BOOL CtrlHandler(DWORD fdwCtrlType)
{
	if (g_hevExit != NULL)
		SetEvent(g_hevExit);
	return TRUE;
}



// ������ Ǯ ������ ��Ʈ�� �Լ�
DWORD WINAPI IocpSockRecvProc(PVOID pParam);

PVOID GetSockExtAPI(SOCKET sock, GUID guidFn);
SOCKET GetListenSocket(short shPortNo, int nBacklog = SOMAXCONN);
void RemoveFailedSockect(PIOCP_ENV pIE, PSOCK_ITEM pSI);
void IncreaseAcceptSockets(PIOCP_ENV pIE, int nIncCnt = PERMIT_INC_CNT);


void _tmain()
{
	WSADATA	wsd;
	int nErrCode = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (nErrCode)
	{
		cout << "WSAStartup failed with error : " << nErrCode << endl;
		return;
	}

	// ���� ���� �̺�Ʈ ����
	g_hevExit = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (g_hevExit == NULL)
	{
		cout << "CreateEvent failed, code : " << GetLastError() << endl;
		WSACleanup();
		return;
	}

	// Ctrl Handler ��ġ
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
	{
		cout << "SetConsoleCtrlHandler failed, code : " << GetLastError() << endl;
		WSACleanup();
		return;
	}


	// CPU ���� ȹ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	PHANDLE parThreads = new HANDLE[si.dwNumberOfProcessors];

	IOCP_ENV ie;
	try
	{
		// ���� ���� ȹ��
		ie._listen = GetListenSocket(SVR_DEF_PORT);
		if (ie._listen == INVALID_SOCKET)
			throw HRESULT_FROM_WIN32(WSAGetLastError());
		cout << " ==> Waiting for client's connection......" << endl;

		// IOCP ���� �� ���� ������ IOCP�� ���
		ie._iocp = CreateIoCompletionPort
		(
			(HANDLE)ie._listen, NULL, IOCP_KEY_LISTEN, si.dwNumberOfProcessors
		);
		if (ie._listen == NULL)
			throw HRESULT_FROM_WIN32(GetLastError());

		// ������ Ǯ�� ���� ������ ����(CPU ������ŭ)
		for (DWORD i = 0; i < si.dwNumberOfProcessors; i++)
		{
			DWORD dwThreadId;
			parThreads[i] = CreateThread(NULL, 0, IocpSockRecvProc, &ie, 0, &dwThreadId);
			if (parThreads[i] == NULL)
				throw HRESULT_FROM_WIN32(GetLastError());
		}

		// Accept ��⸦ ���� ���� Ǯ ���� �̸� ����
		IncreaseAcceptSockets(&ie, PERMIT_INC_CNT);

		// ���� Ǯ �߰� ���� Ž���� ���� �̺�Ʈ ���� �� ���� ���ϰ��� ���� ó��
		WSAEVENT hEvent = WSACreateEvent();
		if (hEvent == NULL)
			throw HRESULT_FROM_WIN32(WSAGetLastError());
		WSAEventSelect(ie._listen, hEvent, FD_ACCEPT);

		HANDLE arSyncObjs[2] = { g_hevExit, hEvent };
		while (true)
		{
			DWORD dwWaitRet = WaitForMultipleObjects(2, arSyncObjs, FALSE, INFINITE);
			if (dwWaitRet == WAIT_FAILED)
			{
				CloseHandle(hEvent);
				throw HRESULT_FROM_WIN32(GetLastError());
			}

			// Ctrl-C�� ���� ���� ����
			if (dwWaitRet == WAIT_OBJECT_0)
				break;

			// ���� ���Ͽ� ����� �̺�Ʈ �ñ׳�, ���� Ǯ�� Accept ���� �ٴڳ� ����.
			WSANETWORKEVENTS ne;
			WSAEnumNetworkEvents(ie._listen, hEvent, &ne);
			if (ne.lNetworkEvents & FD_ACCEPT)
			{
				int nErrCode = ne.iErrorCode[FD_ACCEPT_BIT];
				if (nErrCode > 0)
				{
					CloseHandle(hEvent);
					throw HRESULT_FROM_WIN32(nErrCode);
				}

				// Accept ��⸦ ���� ���� Ǯ ���� �߰� ����
				IncreaseAcceptSockets(&ie, PERMIT_INC_CNT);
			}
		}
		CloseHandle(hEvent);
	}
	catch (HRESULT hr)
	{
		cout << "server error occurred, code : " << hr << endl;
	}

	// ������Ǯ �������� ���� ��� �� ���� ���ҽ� ����
	for (DWORD i = 0; i < si.dwNumberOfProcessors; i++)
		PostQueuedCompletionStatus(ie._iocp, 0, (ULONG_PTR)IOCP_KEY_EXIT, NULL);
	WaitForMultipleObjects(si.dwNumberOfProcessors, parThreads, TRUE, INFINITE);
	for (DWORD i = 0; i < si.dwNumberOfProcessors; i++)
		CloseHandle(parThreads[i]);
	delete[] parThreads;

	// ���� ���ϰ� �ڽ� ���� �ݱ�
	if (ie._listen != INVALID_SOCKET)
		closesocket(ie._listen);
	for (SOCK_SET::iterator it = ie._socks.begin(); it != ie._socks.end(); it++)
	{
		PSOCK_ITEM pSI = *it;
		closesocket(pSI->_sock);
		delete pSI;
	}
	for (SOCK_SET::iterator it = ie._spool.begin(); it != ie._spool.end(); it++)
	{
		PSOCK_ITEM pSI = *it;
		closesocket(pSI->_sock);
		delete pSI;
	}

	// IOCP �ݱ�
	if (ie._iocp != NULL)
		CloseHandle(ie._iocp);

	cout << "==== Server terminates... ==========================" << endl;

	WSACleanup();
}

DWORD WINAPI IocpSockRecvProc(PVOID pParam)
{
	PIOCP_ENV	pIE = (PIOCP_ENV)pParam;
	OVERLAPPED*	pOL = NULL;
	DWORD		dwTranBytes = 0;
	ULONG_PTR	upDevKey = 0;

	while (true)
	{
		BOOL bEndRlt = GetQueuedCompletionStatus
		(
			pIE->_iocp, &dwTranBytes, &upDevKey, &pOL, INFINITE
		);
		if (bEndRlt == FALSE)
		{
			DWORD dwErrCode = GetLastError();
			if (dwErrCode != ERROR_NETNAME_DELETED)
			{
				cout << "GetQueuedCompletionStatus failed : " << dwErrCode << endl;
				break;
			}
		}

		// ������ Ǯ ������ ���� Ű ����
		if (upDevKey == IOCP_KEY_EXIT)
			break;

		PSOCK_ITEM pSI = (PSOCK_ITEM)pOL;
		// ���� ���� �ñ׳� : ������ �̷�� ��.
		if (upDevKey == IOCP_KEY_LISTEN)
		{
			// �ڽ� ������ IOCP�� ����
			CreateIoCompletionPort((HANDLE)pSI->_sock, pIE->_iocp, IOCP_KEY_CHILD, 0);
			printf(" ==> New client %d connected...\n", pSI->_sock);

			// ���� Ǯ���� ���� ȹ��
			EnterCriticalSection(&pIE->_cs);
			pIE->_spool.erase(pSI);
			pIE->_socks.insert(pSI);
			LeaveCriticalSection(&pIE->_cs);
		}
		// �ڽ� ���� �ñ׳� : Ŭ���̾�Ʈ�κ����� ������ ���� �Ǵ� ���� ���� �Ǵ� ���� �߻�
		else
		{
			if (dwTranBytes == 0 || pOL->Internal != 0)
			{
				// ���� �߻�, ���� ���� ó��
				if (pOL->Internal != 0)
				{
					printf(" ~~~ Error occurred with OVERLAPPED.Internal = %d\n", pOL->Internal);
					RemoveFailedSockect(pIE, pSI);
				}
				// Ŭ���̾�Ʈ�� ������ ����
				else
				{
					printf(" ==> Client %d disconnected...\n", pSI->_sock);

					// ���� ������ ���� ������ ���⸸ �ϰ� ���� ����.
					LPFN_DISCONNECTEX pfnDisconnectEx =
						(LPFN_DISCONNECTEX)GetSockExtAPI(pSI->_sock, WSAID_DISCONNECTEX);
					if (pfnDisconnectEx == NULL)
					{
						RemoveFailedSockect(pIE, pSI);
						continue;
					}
					pfnDisconnectEx(pSI->_sock, NULL, TF_REUSE_SOCKET, 0);

					// ���� Ǯ�� ���� ���� ��ȯ
					EnterCriticalSection(&pIE->_cs);
					pIE->_socks.erase(pSI);
					pIE->_spool.insert(pSI);
					LeaveCriticalSection(&pIE->_cs);

					// �񵿱� ���� ��� ���·�...
					LPFN_ACCEPTEX pfnAcceptEx = (LPFN_ACCEPTEX)
						GetSockExtAPI(pIE->_listen, WSAID_ACCEPTEX);
					if (pfnAcceptEx == NULL)
					{
						RemoveFailedSockect(pIE, pSI);
						continue;
					}
					BOOL bIsOK = pfnAcceptEx
					(
						pIE->_listen, pSI->_sock, pSI->_buff, 0,
						sizeof(SOCKADDR_IN) + 16,
						sizeof(SOCKADDR_IN) + 16,
						NULL, (LPOVERLAPPED)pSI
					);
					if (bIsOK == FALSE)
					{
						int nErrCode = WSAGetLastError();
						if (nErrCode != WSA_IO_PENDING)
						{
							printf(" ~~~ AcceptEx failed, ErrorCode = %d\n", nErrCode);
							RemoveFailedSockect(pIE, pSI);
						}
					}
				}
				continue;
			}

			pSI->_buff[dwTranBytes] = 0;
			printf(" *** Client(%d) sent : %s\n", pSI->_sock, pSI->_buff);

			// ���� �����͸� Ŭ���̾�Ʈ�� ����
			int lSockRet = send(pSI->_sock, pSI->_buff, dwTranBytes, 0);
			if (lSockRet == SOCKET_ERROR)
			{
				printf(" ~~~ send failed, ErrorCode = %d\n", WSAGetLastError());
				RemoveFailedSockect(pIE, pSI);
			}
		}

		// �񵿱� ���� ��� ���·�...
		if (!ReadFile((HANDLE)pSI->_sock, pSI->_buff,
			sizeof(pSI->_buff), NULL, (LPOVERLAPPED)pSI))
		{
			int nErrCode = WSAGetLastError();
			if (nErrCode != WSA_IO_PENDING)
			{
				printf(" ~~~ ReadFile failed, ErrorCode = %d\n", nErrCode);
				RemoveFailedSockect(pIE, pSI);
			}
		}
	}

	return 0;
}


PVOID GetSockExtAPI(SOCKET sock, GUID guidFn)
{
	PVOID pfnEx = NULL;
	GUID  guid = guidFn;
	DWORD dwBytes = 0;
	LONG lRet = WSAIoctl
	(
		sock, SIO_GET_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(guid), &pfnEx,
		sizeof(pfnEx), &dwBytes, NULL, NULL
	);
	if (lRet == SOCKET_ERROR)
	{
		cout << "WSAIoctl failed, code : " << WSAGetLastError() << endl;
		return NULL;
	}
	return pfnEx;
}

SOCKET GetListenSocket(short shPortNo, int nBacklog)
{
	SOCKET hsoListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (hsoListen == INVALID_SOCKET)
	{
		cout << "socket failed, code : " << WSAGetLastError() << endl;
		return INVALID_SOCKET;
	}

	SOCKADDR_IN	sa;
	memset(&sa, 0, sizeof(SOCKADDR_IN));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(shPortNo);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	LONG lSockRet = bind(hsoListen, (PSOCKADDR)&sa, sizeof(SOCKADDR_IN));
	if (lSockRet == SOCKET_ERROR)
	{
		cout << "bind failed, code : " << WSAGetLastError() << endl;
		closesocket(hsoListen);
		return INVALID_SOCKET;
	}

	lSockRet = listen(hsoListen, nBacklog);
	if (lSockRet == SOCKET_ERROR)
	{
		cout << "listen failed, code : " << WSAGetLastError() << endl;
		closesocket(hsoListen);
		return INVALID_SOCKET;
	}

	return hsoListen;
}

void RemoveFailedSockect(PIOCP_ENV pIE, PSOCK_ITEM pSI)
{
	EnterCriticalSection(&pIE->_cs);
	pIE->_socks.erase(pSI);
	LeaveCriticalSection(&pIE->_cs);
	closesocket(pSI->_sock);
	delete pSI;
}

void IncreaseAcceptSockets(PIOCP_ENV pIE, int nIncCnt)
{
	for (int i = 0; i < nIncCnt; i++)
	{
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
			throw HRESULT_FROM_WIN32(WSAGetLastError());

		PSOCK_ITEM pSI = new SOCK_ITEM(sock);
		EnterCriticalSection(&pIE->_cs);
		pIE->_spool.insert(pSI);
		LeaveCriticalSection(&pIE->_cs);

		LPFN_ACCEPTEX pfnAcceptEx = (LPFN_ACCEPTEX)
			GetSockExtAPI(pIE->_listen, WSAID_ACCEPTEX);
		if (pfnAcceptEx == NULL)
			throw HRESULT_FROM_WIN32(WSAGetLastError());
		BOOL bIsOK = pfnAcceptEx
		(
			pIE->_listen, sock, pSI->_buff, 0,
			sizeof(SOCKADDR_IN) + 16,
			sizeof(SOCKADDR_IN) + 16,
			NULL, (LPOVERLAPPED)pSI
		);
		if (bIsOK == FALSE)
		{
			int nErrCode = WSAGetLastError();
			if (nErrCode != WSA_IO_PENDING)
				throw HRESULT_FROM_WIN32(nErrCode);
		}
	}
}
