
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "f3.h"
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
	ON_BN_CLICKED(101,onRect)
	ON_BN_CLICKED(102,onEllipse)
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
	
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CRect rect;
	GetClientRect(rect);
	CBitmap mbmap;
	mbmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(&mbmap);
	// TODO: Add your message handler code here
	CBrush brush(RGB(255, 0, 0));
	memdc.SelectObject(&brush);
	memdc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	double x = rect.right/2;
	double y = rect.bottom/2;
	double dx = rect.right*0.25;
	double dy = rect.bottom*0.25;
	if (r1.GetCheck() == 1)
	{
		memdc.Rectangle(x - dx, y - dy, x + dx, y + dy);
	}
	if (r2.GetCheck())
	{
		memdc.Ellipse(x - dx, y - dy, x + dx, y + dy);
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
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
void CChildView::onRect()
{
	r1.SetCheck(1);
	r2.SetCheck(0);
	Invalidate();
}
void CChildView::onEllipse()
{
	r1.SetCheck(0);
	r2.SetCheck(1);
	Invalidate();
}