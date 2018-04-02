
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCApplication3.h"
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
	ON_BN_CLICKED(101,onR1)
	ON_BN_CLICKED(102,onR2)
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
	CRect rect;
	GetClientRect(rect);
	double s=1.0;
	double dx = rect.right*(0.25);
	double dy;
	if (rect.bottom > rect.right)
	{
		s = rect.bottom / rect.right;
		dy = s*dx;
	}
	else
	{
		s = rect.right / rect.bottom;
		dy = dx / s;
	}
	double x = rect.right / 2;
	double y = rect.bottom/ 2;

	// TODO: Add your message handler code here
	CBrush brush(RGB(128, 128, 128));
	dc.SelectObject(&brush);
	if (r1.GetCheck() == 1)
	{
		dc.Rectangle(x - dx, y - dy, x + dx, y + dy);
		//dc.Rectangle(x-50, y-50, x+50, y+50);
	}
	if (r2.GetCheck() == 1)
	{
		dc.Ellipse(x - dx ,y - dy, x + dx, y + dy);
	}
	// Do not call CWnd::OnPaint() for painting messages
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	r1.Create(_T("Rect"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, CRect(0, 0, 100, 30), this, 101);
	r2.Create(_T("Ellipse"), WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON, CRect(100, 0, 200, 30), this, 102);
	// TODO:  Add your specialized creation code here

	return 0;
}
void CChildView::onR1()
{
	r1.SetCheck(1);
	r2.SetCheck(0);
	Invalidate();
}
void CChildView::onR2()
{
	r2.SetCheck(1);
	r1.SetCheck(0);
	Invalidate();
}