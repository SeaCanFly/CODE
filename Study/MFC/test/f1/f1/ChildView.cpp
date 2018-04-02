
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "f1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
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
	POSITION pos = ll.GetHeadPosition();
	while (pos)
	{
		POSITION lpos = ll.GetAt(pos)->GetHeadPosition();
		CPoint prept = ll.GetAt(pos)->GetAt(lpos);
		while (lpos)
		{
			CPoint pt = ll.GetAt(pos)->GetAt(lpos);
			dc.MoveTo(prept);
			dc.LineTo(pt);
			prept = pt;
			ll.GetAt(pos)->GetNext(lpos);
		}
		ll.GetNext(pos);
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	l[count].AddTail(point);
	Invalidate();
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ll.AddTail(&l[count]);
	count++;
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	ll.RemoveTail();
	count--;
	Invalidate();
	// TODO: Add your message handler code here and/or call default

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == VK_LBUTTON)
	{
		l[count].AddTail(point);
		Invalidate();
	}
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}
