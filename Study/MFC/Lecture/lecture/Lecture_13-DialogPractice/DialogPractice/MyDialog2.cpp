// MyDialog2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "DialogPractice.h"
#include "MyDialog2.h"
#include "afxdialogex.h"

#include "ChildView.h"

// CMyDialog2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMyDialog2, CDialogEx)

CMyDialog2::CMyDialog2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialog2::IDD, pParent)
{
}

CMyDialog2::~CMyDialog2()
{

}

void CMyDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_STR, m_edit);
	DDX_Text(pDX, IDC_EDIT_STR, m_str);
	DDX_Control(pDX, IDC_RADIO_RED, m_colorRadio[0]);
	DDX_Control(pDX, IDC_RADIO_GREEN, m_colorRadio[1]);
	DDX_Control(pDX, IDC_RADIO_BLUE, m_colorRadio[2]);
}


BEGIN_MESSAGE_MAP(CMyDialog2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CMyDialog2::OnClickedButtonApply)
	ON_BN_CLICKED(IDCANCEL, &CMyDialog2::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CMyDialog2::OnClickedButtonColor)
END_MESSAGE_MAP()


// CMyDialog2 메시지 처리기입니다.

BOOL CMyDialog2::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_edit.SetWindowText(m_str);	// DDX_TEXT로 m_str과 자동으로 연결되어 필요없음. 

	m_colorRadio[m_color].SetCheck(true);

	return true;
}

void CMyDialog2::OnClickedButtonApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);		// DDX를 직접 동작시킨다.
	
	for(int i = 0; i < 3; i++)
		if(m_colorRadio[i].GetCheck())
			m_color = i;

	m_pView->m_str = m_str;
	m_pView->m_color = m_color;
	m_pView->m_userColor = m_userColor;
	m_pView->Invalidate();	// WM_PAINT 메세지 발생 --> OnPaint() 함수 실행
}


void CMyDialog2::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
//	delete m_pView->m_pDlg;
//	m_pView->m_pDlg = NULL;
//	CDialogEx::OnCancel();
}

void CMyDialog2::OnClickedButtonColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog dlg(RGB(255, 255, 255), CC_FULLOPEN);
	dlg.DoModal();
	m_userColor = dlg.GetColor(); 
}

void CMyDialog2::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_pView->m_pDlg = NULL;
	delete this;		// 대화상자 객체를 파괴

//	CDialogEx::PostNcDestroy();
}



