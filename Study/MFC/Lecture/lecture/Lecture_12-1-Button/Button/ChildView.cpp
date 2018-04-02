
// ChildView.cpp : CChildView Ŭ������ ����
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



// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_pushButton1.Create(_T("��ư 1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 100, 200, 130), this, 101); // Ǫ�� ��ư 1 ����
	m_pushButton2.Create(_T("��ư 2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 200, 200, 230), this, 102); // Ǫ�� ��ư 2 ����

	m_checkBox1.Create(_T("üũ �ڽ� 1"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(100, 300, 300, 330), this, 103); // üũ �ڽ� 1 ����
	m_checkBox2.Create(_T("üũ �ڽ� 2"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, CRect(100, 400, 300, 430), this, 104); // üũ �ڽ� 2 ����

	return 0;
}

void CChildView::OnButton1Clicked()
{
	AfxMessageBox(_T("��ư 1�� ���Ƚ��ϴ�."));
}

void CChildView::OnButton2Clicked()
{
	AfxMessageBox(_T("��ư 2�� ���Ƚ��ϴ�."));
}

void CChildView::OnCheckBox1Clicked()
{
	if (m_checkBox1.GetCheck() == BST_UNCHECKED)
		m_checkBox1.SetCheck(BST_CHECKED);
	else if (m_checkBox1.GetCheck() == BST_CHECKED)
		m_checkBox1.SetCheck(BST_UNCHECKED);

	AfxMessageBox(_T("üũ �ڽ� 1�� ���Ƚ��ϴ�."));
}

void CChildView::OnCheckBox2Clicked()
{
	if (m_checkBox2.GetCheck() == BST_UNCHECKED)
		m_checkBox2.SetCheck(BST_CHECKED);
	else if (m_checkBox2.GetCheck() == BST_CHECKED)
		m_checkBox2.SetCheck(BST_UNCHECKED);

	AfxMessageBox(_T("üũ �ڽ� 2�� ���Ƚ��ϴ�."));
}