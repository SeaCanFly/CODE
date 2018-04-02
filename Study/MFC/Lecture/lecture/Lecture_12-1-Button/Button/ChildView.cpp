
// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Button.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(101, OnButton1Clicked)
	ON_BN_CLICKED(102, OnButton2Clicked)
	ON_BN_CLICKED(103, OnCheckBox1Clicked)
	ON_BN_CLICKED(104, OnCheckBox2Clicked)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_pushButton1.Create(_T("버튼 1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 100, 200, 130), this, 101); // 푸시 버튼 1 생성
	m_pushButton2.Create(_T("버튼 2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 200, 200, 230), this, 102); // 푸시 버튼 2 생성

	m_checkBox1.Create(_T("체크 박스 1"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(100, 300, 300, 330), this, 103); // 체크 박스 1 생성
	m_checkBox2.Create(_T("체크 박스 2"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(100, 400, 300, 430), this, 104); // 체크 박스 2 생성

	return 0;
}

void CChildView::OnButton1Clicked()
{
	AfxMessageBox(_T("버튼 1을 눌렸습니다."));
}

void CChildView::OnButton2Clicked()
{
	AfxMessageBox(_T("버튼 2을 눌렸습니다."));
}

void CChildView::OnCheckBox1Clicked()
{
	if (m_checkBox1.GetCheck() == BST_UNCHECKED)
		m_checkBox1.SetCheck(BST_CHECKED);
	else if (m_checkBox1.GetCheck() == BST_CHECKED)
		m_checkBox1.SetCheck(BST_UNCHECKED);

	AfxMessageBox(_T("체크 박스 1을 눌렸습니다."));
}

void CChildView::OnCheckBox2Clicked()
{
	if (m_checkBox2.GetCheck() == BST_UNCHECKED)
		m_checkBox2.SetCheck(BST_CHECKED);
	else if (m_checkBox2.GetCheck() == BST_CHECKED)
		m_checkBox2.SetCheck(BST_UNCHECKED);

	AfxMessageBox(_T("체크 박스 2을 눌렸습니다."));
}