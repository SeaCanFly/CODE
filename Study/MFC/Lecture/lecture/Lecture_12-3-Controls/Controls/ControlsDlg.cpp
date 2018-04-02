// ControlsDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Controls.h"
#include "ControlsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
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


// CControlsDlg 대화 상자



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


// CControlsDlg 메시지 처리기

BOOL CControlsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Edit.SetWindowText(_T("초기화합니다."));

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CControlsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	
		CDialog::OnPaint();


	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CControlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CControlsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString str1;
	if (m_checkButton.GetCheck()) 
		str1 = _T("체크박스1이 선택됨");
	else 
		str1 = _T("체크박스1이 선택안됨");

	CString str2;
	if (m_RadioButton1.GetCheck()) 
		str2 = _T("라디오버튼1이 선택됨");
	else 
		str2 = _T("라디오버튼1이 선택안됨");

	CString str3;
	if (m_RadioButton2.GetCheck()) 
		str3 = _T("라디오버튼2이 선택됨");
	else 
		str3 = _T("라디오버튼2이 선택안됨");

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
