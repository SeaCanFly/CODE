#include "stdafx.h"
#include "ChatASClient.h"
#include "ChatASClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void ShowErrMsg(DWORD dwErrCode)
{
	LPVOID	lpMsgBuf;
	CString szMsg;

	int nCharCnt = ::FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dwErrCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL
	);
	if (nCharCnt == 0)
		szMsg.Format(_T("Unknown error, ErrorCode : 0x%08X"), dwErrCode);
	else
		szMsg.Format(_T("%s (0x%08X)"), (LPCTSTR)lpMsgBuf, dwErrCode);
	::LocalFree(lpMsgBuf);
	AfxMessageBox(szMsg);
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatASClientDlg ��ȭ ����



CChatASClientDlg::CChatASClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatASClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSock = INVALID_SOCKET;
}

void CChatASClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatASClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CChatASClientDlg::OnBnClickedOk)
	ON_MESSAGE(WM_SOCK_NOTI, OnSockNoti)
END_MESSAGE_MAP()


// CChatASClientDlg �޽��� ó����

BOOL CChatASClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString szId;
	szId.Format(_T("Chatting : %d"), GetCurrentProcessId());
	SetWindowText(szId);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CChatASClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CChatASClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CChatASClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CChatASClientDlg::UpdateChatView(PCTSTR pszMsg)
{

}

void CChatASClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_hSock != INVALID_SOCKET)
		closesocket(m_hSock);
}

void CChatASClientDlg::OnBnClickedOk()
{
	if (m_hSock == INVALID_SOCKET)
	{
		m_hSock = socket(AF_INET, SOCK_STREAM, 0);
		if (m_hSock == INVALID_SOCKET)
			throw HRESULT_FROM_WIN32(WSAGetLastError());

		WSAAsyncSelect
		(
			m_hSock, this->GetSafeHwnd(), 
			WM_SOCK_NOTI, FD_CONNECT| FD_READ | FD_CLOSE
		);

		SOCKADDR_IN	sa;
		memset(&sa, 0, sizeof(SOCKADDR_IN));
		sa.sin_family		= AF_INET;
		sa.sin_port			= htons(9001);
		sa.sin_addr.s_addr	= inet_addr("127.0.0.1");
		int lSockRet = connect(m_hSock, (LPSOCKADDR)&sa, sizeof(sa));
		if (lSockRet == SOCKET_ERROR)
		{
			LONG lErrCode = WSAGetLastError();
			if (lErrCode != WSAEWOULDBLOCK)
			{
				ShowErrMsg(lErrCode);
				closesocket(m_hSock);
				m_hSock = INVALID_SOCKET;
			}
		}
	}
	else
	{
		CString szId;
		szId.Format(_T("%d >> "), GetCurrentProcessId());
		
		CString szBuff;
		GetDlgItemText(IDC_EDIT_INPUT, szBuff);
		szBuff.Insert(0, szId);

		int lSockRet = send(m_hSock, (PCSTR)(LPCTSTR)szBuff, 
			szBuff.GetLength() * sizeof(TCHAR), 0);
		if (lSockRet == SOCKET_ERROR)
		{
			ShowErrMsg(WSAGetLastError());
			closesocket(m_hSock);
			m_hSock = INVALID_SOCKET;

			GetDlgItem(IDC_EDIT_CHAT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_INPUT)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->SetWindowText(_T("����"));
		}
		else
		{
			szBuff.Append(_T("\xd\xa"));
			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CHAT);
			int nInsPos = pEdit->GetWindowTextLength();
			pEdit->SetSel(nInsPos, nInsPos);
			pEdit->ReplaceSel(szBuff);

			SetDlgItemText(IDC_EDIT_INPUT, _T(""));
		}
	}
}

LRESULT CChatASClientDlg::OnSockNoti(WPARAM wParam, LPARAM lParam)
{
	SOCKET	sock = (SOCKET)wParam;
	LONG	lErrCode = WSAGETSELECTERROR(lParam);
	WORD	wFDFlags = WSAGETSELECTEVENT(lParam);

	if (lErrCode != 0)
	{
		ShowErrMsg(lErrCode);
		closesocket(sock);
		m_hSock = INVALID_SOCKET;

		GetDlgItem(IDC_EDIT_CHAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_INPUT)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->SetWindowText(_T("����"));
		return 0;
	}

	switch (wFDFlags)
	{
		case FD_CONNECT:
		{
			GetDlgItem(IDC_EDIT_CHAT)->EnableWindow();
			GetDlgItem(IDC_EDIT_INPUT)->EnableWindow();
			GetDlgItem(IDOK)->SetWindowText(_T("����"));
		}
		break;

		case FD_READ:
		{
			TCHAR szBuff[65536];
			int lSockRet = recv(sock, (PCHAR)szBuff, 65536 * sizeof(TCHAR), 0);
			szBuff[lSockRet / sizeof(TCHAR)] = 0;
			_tcscat_s(szBuff, _T("\xd\xa"));

			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CHAT);
			int nInsPos = pEdit->GetWindowTextLength();
			pEdit->SetSel(nInsPos, nInsPos);
			pEdit->ReplaceSel(szBuff);
		}
		break;

		case FD_CLOSE:
		{
			SOCKET sock = (SOCKET)wParam;
			closesocket(sock);
			m_hSock = INVALID_SOCKET;

			GetDlgItem(IDC_EDIT_CHAT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_INPUT)->EnableWindow(FALSE);
			GetDlgItem(IDOK)->SetWindowText(_T("����"));
		}
		break;
	}
	return 0;
}
