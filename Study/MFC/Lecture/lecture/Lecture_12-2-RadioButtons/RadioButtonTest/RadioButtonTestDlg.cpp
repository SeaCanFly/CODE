// RadioButtonTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RadioButtonTest.h"
#include "RadioButtonTestDlg.h"
#include ".\radiobuttontestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRadioButtonTestDlg 대화 상자



CRadioButtonTestDlg::CRadioButtonTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRadioButtonTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRadioButtonTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRadioButtonTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_RADIO1, IDC_RADIO6, OnRadioClick)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CRadioButtonTestDlg 메시지 처리기

BOOL CRadioButtonTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	m_SelectedRadio = 0;

	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CRadioButtonTestDlg::OnPaint() 
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
HCURSOR CRadioButtonTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRadioButtonTestDlg::OnRadioClick(UINT nID)
{


	switch(nID)
	{
	case IDC_RADIO1:
		m_SelectedRadio = 1;	break;
	case IDC_RADIO2:
		m_SelectedRadio = 2;	break;
	case IDC_RADIO3:
		m_SelectedRadio = 3;	break;
	case IDC_RADIO4:
		m_SelectedRadio = 4;	break;
	case IDC_RADIO5:
		m_SelectedRadio = 5;	break;
	case IDC_RADIO6:
		m_SelectedRadio = 6;	break;
	default:
		break;
	}

	
}

void CRadioButtonTestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	if (m_SelectedRadio == 0)
		str.Format(_T("라디오 버튼이 선택되지 않았음"));
	else
		str.Format(_T("선택된 라디오 버튼: %d"), m_SelectedRadio);
	AfxMessageBox(str);

}
