// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ScrollCircle.h"
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
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
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

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	dc.Ellipse(m_pt.x-50, m_pt.y-50, m_pt.x+50, m_pt.y+50);
	
	// Do not call CWnd::OnPaint() for painting messages
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// 윈도우 스크롤 바 표시
//	this->ShowScrollBar(SB_BOTH, true);	

	// 스크롤 바 콘트롤 생성
	m_HBar.Create(SBS_HORZ, CRect(0, 0, 400, 20), this, 101);
	m_VBar.Create(SBS_VERT, CRect(0, 0, 20, 400), this, 102);
	
	m_HBar.ShowWindow(true);
	m_VBar.ShowWindow(true);

	m_pt = CPoint(200,200);

	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
/*
	// 윈도우 스크롤 바 조절	
	this->SetScrollRange(SB_HORZ, 0, cx);
	this->SetScrollRange(SB_VERT, 0, cy);

	this->SetScrollPos(SB_HORZ, m_pt.x);
	this->SetScrollPos(SB_VERT, m_pt.y);
*/
	// 스크롤 바 콘트롤 크기 조절
	m_HBar.SetWindowPos(this, 0, 0, cx - 20, 20, SWP_NOZORDER);
	m_VBar.SetWindowPos(this, cx - 20, 20, cx, cy - 20, SWP_NOZORDER);

	m_HBar.SetScrollRange(20, cx - 40);
	m_VBar.SetScrollRange(40, cy - 40);

	m_HBar.SetScrollPos(m_pt.x);
	m_VBar.SetScrollPos(m_pt.y);

	// TODO: Add your message handler code here
}

void CChildView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
/*
	// 윈도우 스크롤 바로 원의 위치 업데이트
	if (pScrollBar == NULL) {
		if (pScrollBar== this->GetScrollBarCtrl(SB_VERT)) {
			if(nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
				this->SetScrollPos(SB_VERT, nPos);
				m_pt.y = nPos;
				this->Invalidate();
			}
		}
	} 
*/

	// 스크롤 바 콘트롤로 윈의 위치 업데이트
	if (pScrollBar != NULL) {
		if (pScrollBar->GetSafeHwnd() == m_VBar.GetSafeHwnd()) {
			if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
				pScrollBar->SetScrollPos(nPos);
				m_pt.y = nPos;
				this->Invalidate();
			}
		}
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
/*
	// 윈도우 스크롤 바로 원의 위치 업데이트
	if (pScrollBar == NULL) {
		if (pScrollBar== this->GetScrollBarCtrl(SB_HORZ)) {
			if(nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
				this->SetScrollPos(SB_HORZ, nPos);
				m_pt.x = nPos;
				this->Invalidate();
			}
		}
	} 
*/
	// 스크롤 바 콘트롤로 윈의 위치 업데이트
	if (pScrollBar != NULL) {
		if (pScrollBar->GetSafeHwnd() == m_HBar.GetSafeHwnd()) {
			if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
				pScrollBar->SetScrollPos(nPos);
				m_pt.x = nPos;
				this->Invalidate();
			}
		}
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}
