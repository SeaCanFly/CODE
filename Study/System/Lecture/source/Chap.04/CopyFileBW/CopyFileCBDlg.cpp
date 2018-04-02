
// CopyFileCBDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CopyFileCB.h"
#include "CopyFileCBDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CCopyFileCBDlg ��ȭ ����



CCopyFileCBDlg::CCopyFileCBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCopyFileCBDlg::IDD, pParent)
	, m_szSrc(_T(""))
	, m_szDst(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hPause = NULL;
}

void CCopyFileCBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRC, m_szSrc);
	DDX_Text(pDX, IDC_EDIT_DST, m_szDst);
}

BEGIN_MESSAGE_MAP(CCopyFileCBDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SRC, &CCopyFileCBDlg::OnBnClickedBtnSrc)
	ON_BN_CLICKED(IDC_BTN_DST, &CCopyFileCBDlg::OnBnClickedBtnDst)
	ON_BN_CLICKED(IDOK, &CCopyFileCBDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CCopyFileCBDlg::OnBnClickedPause)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CCopyFileCBDlg �޽��� ó����
BOOL CCopyFileCBDlg::OnInitDialog()
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
	((CProgressCtrl*)GetDlgItem(IDC_PRG_COPY))->SetRange(0, 100);

	m_hPause = CreateEvent(NULL, TRUE, TRUE, NULL);

	m_bw.Initialize(GetSafeHwnd(), Handler_DoWork);
	m_bw.SetReportHandler(Handler_Report);
	m_bw.SetCompletedHandler(Handler_Completed);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCopyFileCBDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_bw.Uninitialize();
	if (m_hPause != NULL)
		CloseHandle(m_hPause);
}

void CCopyFileCBDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCopyFileCBDlg::OnPaint()
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
HCURSOR CCopyFileCBDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCopyFileCBDlg::OnBnClickedBtnSrc()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		m_szSrc = dlg.GetPathName();
		UpdateData(FALSE);
	}
}


void CCopyFileCBDlg::OnBnClickedBtnDst()
{
	CFileDialog dlg(FALSE, NULL, NULL, 
		OFN_CREATEPROMPT | OFN_FILEMUSTEXIST | 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		_T("All Files(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		m_szDst = dlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CCopyFileCBDlg::OnBnClickedOk()
{
	UpdateData();

	CString szTitle;
	if (!m_bw.IsBusy)
	{
		m_bw.RunWorkerAsync(this);

		SetDlgItemText(IDOK, _T("���"));
		GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_PAUSE)->EnableWindow();
	}
	else
	{
		ResetEvent(m_hPause);
		INT nRlt = AfxMessageBox(_T("�������Դϴ�. �����Ͻðڽ��ϱ�?"), MB_YESNO);
		if (nRlt == IDYES)
			m_bw.CancelAsync();
		SetEvent(m_hPause);
	}
}

void CCopyFileCBDlg::OnBnClickedPause()
{
	CString szTitle;
	GetDlgItemText(IDC_BTN_PAUSE, szTitle);
	if (szTitle == _T("����"))
	{
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		SetDlgItemText(IDC_BTN_PAUSE, _T("���"));
		ResetEvent(m_hPause);
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow();
		SetDlgItemText(IDC_BTN_PAUSE, _T("����"));
		SetEvent(m_hPause);
	}
}

void CCopyFileCBDlg::OnCancel()
{
	if (m_bw.IsBusy)
	{
		ResetEvent(m_hPause);
		if (AfxMessageBox(_T("�������Դϴ�. �����Ͻðڽ��ϱ�?"), MB_YESNO) == IDYES)
			m_bw.CancelAsync();
		SetEvent(m_hPause);
	}

	CDialogEx::OnCancel();
}


void WINAPI CCopyFileCBDlg::Handler_DoWork(BkgrdWorker* pBW, DoWorkArgs* e)
{
	CCopyFileCBDlg* pDlg = (CCopyFileCBDlg*)e->Argument;
	pDlg->DoWork(e);
}

void WINAPI CCopyFileCBDlg::Handler_Report(BkgrdWorker* pBW, ProgressChangedArgs* e)
{
	CCopyFileCBDlg*	pDlg = (CCopyFileCBDlg*)CWnd::FromHandle(pBW->Owner());
	pDlg->Report(e);
}

void WINAPI CCopyFileCBDlg::Handler_Completed(BkgrdWorker* pBW, RunWorkerCompletedArgs* e)
{
	CCopyFileCBDlg*	pDlg = (CCopyFileCBDlg*)CWnd::FromHandle(pBW->Owner());
	pDlg->Completed(e);
}


void CCopyFileCBDlg::DoWork(DoWorkArgs* e)
{
	DWORD	dwErrCode = 0;
	BYTE	btBuff[65536];
	HANDLE	hSrcFile = INVALID_HANDLE_VALUE;
	HANDLE	hDstFile = INVALID_HANDLE_VALUE;

	__int64* psi = new _int64[2];
	psi[0] = psi[1] = 0LL;

	__try
	{
		hSrcFile = CreateFile
		(
			m_szSrc, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL
		);
		if (hSrcFile == INVALID_HANDLE_VALUE)
			throw HRESULT_FROM_WIN32(GetLastError());

		hDstFile = CreateFile
		(
			m_szDst, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL
		);
		if (hDstFile == INVALID_HANDLE_VALUE)
			throw HRESULT_FROM_WIN32(GetLastError());

		LARGE_INTEGER llSrcSize;
		GetFileSizeEx(hSrcFile, &llSrcSize);
		psi[1] = llSrcSize.QuadPart;
		m_bw.ReportProgress(0, psi);

		LARGE_INTEGER llCopiedSize;
		llCopiedSize.QuadPart = 0;
		while (llCopiedSize.QuadPart < llSrcSize.QuadPart)
		{
			if (m_bw.CancellationPending)
			{
				e->Cancel = true;
				break;
			}

			DWORD dwReadBytes = 0;
			BOOL bIsOK = ReadFile
			(
				hSrcFile, btBuff, sizeof(btBuff), &dwReadBytes, NULL
			);
			if (!bIsOK)
				throw HRESULT_FROM_WIN32(GetLastError());

			DWORD dwWroteBytes = 0;
			bIsOK = WriteFile
			(
				hDstFile, btBuff, dwReadBytes, &dwWroteBytes, NULL
			);
			if (!bIsOK)
				throw HRESULT_FROM_WIN32(GetLastError());

			llCopiedSize.QuadPart += dwWroteBytes;

			int nPercent = (int)(llCopiedSize.QuadPart * 100LL / llSrcSize.QuadPart);
			psi[0] = llCopiedSize.QuadPart;
			m_bw.ReportProgress(nPercent, psi);

			WaitForSingleObject(m_hPause, INFINITE);
		}
	}
	__finally
	{
		e->Result = psi;
		if (hSrcFile != INVALID_HANDLE_VALUE)
			CloseHandle(hSrcFile);
		if (hDstFile != INVALID_HANDLE_VALUE)
			CloseHandle(hDstFile);
	}
}

void CCopyFileCBDlg::Report(ProgressChangedArgs* e)
{
	((CProgressCtrl*)GetDlgItem(IDC_PRG_COPY))->SetPos(e->ProgressPercentage);
	__int64* psi = (__int64*)e->UserState;

	CString szLog;
	szLog.Format(_T("%I64d / %I64d => %d%% Copied...."), psi[0], psi[1], e->ProgressPercentage);
	SetDlgItemText(IDC_EDIT_INFO, szLog);
}

void CCopyFileCBDlg::Completed(RunWorkerCompletedArgs* e)
{
	//if (m_bClosing)
	//{
	//	pDlg->DestroyWindow();
	//	return;
	//}

	__int64* psi = (__int64*)e->Result;
	CString szLog;

	if (FAILED(e->Error))
		szLog.Format(_T("Error occurred, code is %08X...\n"), e->Error);
	else
	{
		if (e->Cancelled)
			szLog.Format(_T("%I64d bytes copied, but canceled...\n"), psi[0]);
		else
			szLog.Format(_T("Total %I64d bytes copy completed...\n"), psi[1]);
	}
	SetDlgItemText(IDC_EDIT_INFO, szLog);
	delete[] psi;

	SetDlgItemText(IDOK, _T("����"));
	GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(FALSE);
	SetDlgItemText(IDC_BTN_PAUSE, _T("����"));
}
