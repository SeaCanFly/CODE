
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	is_lbutton_down = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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
	int num = pl.plist.GetCount();
	pl.drawPoint(&dc);
	CString str;
	str.Format(_T("%d"), num);
	dc.TextOutW(0, 0, str);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	is_lbutton_down = 1;
	pl.drawSavePoint(&dc, point);
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	is_lbutton_down = 0;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	if (is_lbutton_down)
	{
		pl.drawSavePoint(&dc, point);
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	startp = point;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	dc.Rectangle(CRect(startp, point));
	pl.cleanPoint(startp, point);
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}
