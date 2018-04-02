
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
	m_dwState = PROGRESS_CONTINUE;
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
	ON_MESSAGE(WM_COPY_PROGRESS, OnCopyProgress)
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

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCopyFileCBDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_hPause != NULL)
		CloseHandle(m_hPause);
	if (m_hWorker != NULL)
		CloseHandle(m_hWorker);
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
	GetDlgItemText(IDOK, szTitle);
	if (szTitle == _T("����"))
	{
		m_dwState = PROGRESS_CONTINUE;

		DWORD dwThreadId;
		m_hWorker = CreateThread(NULL, 0, WorkerProc, this, 0, &dwThreadId);
		if (m_hWorker == NULL)
		{

		}
		SetDlgItemText(IDOK, _T("���"));
		GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(TRUE);
		GetDlgItem(IDC_BTN_PAUSE)->EnableWindow();
	}
	else
	{
		m_dwState = PROGRESS_CANCEL;
		WaitForSingleObject(m_hWorker, INFINITE);
		CloseHandle(m_hWorker);
		m_hWorker = NULL;

		SetDlgItemText(IDOK, _T("����"));
		GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(FALSE);
		SetDlgItemText(IDC_BTN_PAUSE, _T("����"));

		PostMessage(WM_COPY_PROGRESS, 0, 0);
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
	if (m_hWorker != NULL)
	{
		ResetEvent(m_hPause);
		if (AfxMessageBox(_T("�������Դϴ�. �����Ͻðڽ��ϱ�?"), MB_YESNO) == IDYES)
		{
			m_dwState = PROGRESS_STOP;
			SetEvent(m_hPause);
			WaitForSingleObject(m_hWorker, INFINITE);
			CloseHandle(m_hWorker);
			m_hWorker = NULL;
		}
		else
			SetEvent(m_hPause);
	}

	CDialogEx::OnCancel();
}

DWORD WINAPI CCopyFileCBDlg::WorkerProc(PVOID pParam)
{
	CCopyFileCBDlg* pDlg = (CCopyFileCBDlg*)pParam;
	CopyFileEx(pDlg->m_szSrc, pDlg->m_szDst, CopyProgressRoutine, pDlg, NULL, 0);
	return 0;
}

LRESULT CCopyFileCBDlg::OnCopyProgress(WPARAM wParam, LPARAM lParam)
{
	__int64* pSizeInfo = (__int64*)lParam;
	if (pSizeInfo == NULL)
	{
		((CProgressCtrl*)GetDlgItem(IDC_PRG_COPY))->SetPos(0);
		GetDlgItem(IDC_EDIT_INFO)->SetWindowText(_T(""));
	}
	else
	{
		__int64 llTotal = pSizeInfo[1], llCopied = pSizeInfo[0];
		delete[] pSizeInfo;

		int nPerc = (int)(llCopied * 100L / llTotal);
		((CProgressCtrl*)GetDlgItem(IDC_PRG_COPY))->SetPos(nPerc);

		CString szInfo;
		szInfo.Format(_T("%I64d / %I64d => %d %% ������..."), llCopied, llTotal, nPerc);
		GetDlgItem(IDC_EDIT_INFO)->SetWindowText(szInfo);

		if (llCopied == llTotal)
		{
			szInfo.Format(_T(">>>> %I64d ����Ʈ ���� �Ϸ� <<<<<"), llTotal);
			GetDlgItem(IDC_EDIT_INFO)->SetWindowText(szInfo);

			m_dwState = PROGRESS_QUIET;
			WaitForSingleObject(m_hWorker, INFINITE);
			CloseHandle(m_hWorker);
			m_hWorker = NULL;

			SetDlgItemText(IDOK, _T("����"));
			GetDlgItem(IDC_BTN_PAUSE)->EnableWindow(FALSE);
			GetDlgItem(IDC_BTN_PAUSE)->ShowWindow(FALSE);
			SetDlgItemText(IDC_BTN_PAUSE, _T("����"));
		}
	}
	return 0;
}

DWORD CALLBACK CCopyFileCBDlg::CopyProgressRoutine(
	LARGE_INTEGER llTotalSize,
	LARGE_INTEGER llTranBytes,
	LARGE_INTEGER llStrmSize,
	LARGE_INTEGER llStrmBytes,
	DWORD dwStrmNum,
	DWORD dwCbReason,
	HANDLE hSrcFile,
	HANDLE hDstFile,
	LPVOID pData
	)
{
	CCopyFileCBDlg* pDlg = (CCopyFileCBDlg*)pData;

	__int64* pSizeInfo = new __int64[2];
	pSizeInfo[0] = llTranBytes.QuadPart;
	pSizeInfo[1] = llTotalSize.QuadPart;
	pDlg->PostMessage(WM_COPY_PROGRESS, 0, (LPARAM)pSizeInfo);

	WaitForSingleObject(pDlg->m_hPause, INFINITE);

	return pDlg->m_dwState;
}
