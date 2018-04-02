
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "6.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dr = 10;
	r = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
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
	CBrush brush(clr);
	dc.SelectObject(&brush);
	// TODO: Add your message handler code here
	dc.Ellipse(mousp.x - r, mousp.y - r, mousp.x + r, mousp. y + r);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mousp = point;
	CWnd::OnMouseMove(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(0, 30, NULL);
	SetTimer(1, 100, NULL);
	// TODO:  Add your specialized creation code here

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (0 == nIDEvent)
	{
		if (r > 50)
		{
			dr = -10;
		}
		if (r < 0)
		{
			dr = 10;
		}
		r = r + dr;
		Invalidate();
	}
	if (1 == nIDEvent)
	{
		clr = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
	CWnd::OnTimer(nIDEvent);
}
