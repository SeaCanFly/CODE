// ControlsDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Controls.h"
#include "ControlsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	



END_MESSAGE_MAP()


// CControlsDlg ��ȭ ����



CControlsDlg::CControlsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CControlsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CControlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_checkButton);
	DDX_Control(pDX, IDC_RADIO1, m_RadioButton1);
	DDX_Control(pDX, IDC_RADIO2, m_RadioButton2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}

BEGIN_MESSAGE_MAP(CControlsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_STN_CLICKED(IDC_STATIC_IMAGE, OnStnClickedStaticImage)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	//ON_STN_CLICKED(IDC_STATIC_IMAGE2, &CControlsDlg::OnStnClickedStaticImage2)
END_MESSAGE_MAP()


// CControlsDlg �޽��� ó����

BOOL CControlsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Edit.SetWindowText(_T("�ʱ�ȭ�մϴ�."));

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CControlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CControlsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

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
	
		CDialog::OnPaint();


	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CControlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CControlsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString str1;
	if (m_checkButton.GetCheck()) 
		str1 = _T("üũ�ڽ�1�� ���õ�");
	else 
		str1 = _T("üũ�ڽ�1�� ���þȵ�");

	CString str2;
	if (m_RadioButton1.GetCheck()) 
		str2 = _T("������ư1�� ���õ�");
	else 
		str2 = _T("������ư1�� ���þȵ�");

	CString str3;
	if (m_RadioButton2.GetCheck()) 
		str3 = _T("������ư2�� ���õ�");
	else 
		str3 = _T("������ư2�� ���þȵ�");

	CString str = str1 + "\n" + str2 + "\n" + str3;
	AfxMessageBox(str);	

}

void CControlsDlg::OnStnClickedStaticImage()
{
	// TODO: Add your control notification handler code here
	AfxMessageBox(_T("Image Clicked"));
}

void CControlsDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Edit.GetWindowText(str);
	if(str.IsEmpty()) return;

	m_ListBox.AddString(str);
	m_Edit.SetSel(0, str.GetLength());
	m_Edit.Clear();

}

void CControlsDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	int index = m_ListBox.GetCurSel();
	if(index != LB_ERR)
		m_ListBox.DeleteString(index);
	

}


void CControlsDlg::OnStnClickedStaticImage2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
