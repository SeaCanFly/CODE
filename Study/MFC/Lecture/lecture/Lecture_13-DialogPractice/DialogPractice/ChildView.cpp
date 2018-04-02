// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "DialogPractice.h"
#include "ChildView.h"

#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = 0;
	m_pDlg = NULL;
	m_userColor = RGB(255, 255, 255);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView message handlers

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

COLORREF g_color[3]={RGB(255,0,0), RGB(0,255,0), RGB(0,0,255)};

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	CRect rect(100, 100, 300, 300);

	dc.Rectangle(rect);

	if (m_userColor == RGB(255, 255, 255))
		dc.SetTextColor(g_color[m_color]);
	else
		dc.SetTextColor(m_userColor);

	rect.DeflateRect(2,2);
	dc.DrawText(m_str, rect, DT_LEFT);

	// Do not call CWnd::OnPaint() for painting messages
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CMyDialog dlg;

	dlg.m_str = m_str;
	dlg.m_color = m_color;

	if (dlg.DoModal() != IDOK) 
		return;

	m_str = dlg.m_str;
	m_color = dlg.m_color;
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pDlg != NULL)
		m_pDlg->SetFocus();
	else {
		m_pDlg = new CMyDialog2();
		m_pDlg->m_pView = this;
		m_pDlg->m_str = m_str;
		m_pDlg->m_color = m_color;
		m_pDlg->m_userColor = m_userColor;
		m_pDlg->Create(IDD_DIALOG2);
		m_pDlg->ShowWindow(SW_SHOW);
	}

	CWnd::OnRButtonDown(nFlags, point);
}
