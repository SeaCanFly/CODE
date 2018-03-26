
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "t1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
	is_lbutton_down = 0;
	is_rbutton_down = 0;
	flag = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//	ON_WM_ERASEBKGND()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap membp;
	membp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(&membp);
	memdc.FillSolidRect(0,0,rect.Width(),rect.Height(), RGB(255, 255, 255));
	if (flag == 1)
	{
		pl.cleenPoint(startp, endp);
		flag = 0;
	}
	
	int num = pl.plist.GetCount();
	for (int i = 0; i < num; i++)
	{
		POSITION pos = pl.plist.FindIndex(i);
		CPoint p = pl.plist.GetAt(pos);
		pl.drawPoint(&memdc, p);
	}

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	// TODO: Add your message handler code here

	CString str;
	str.Format(_T("%d"), num);
	dc.TextOutW(0, 0, str);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	// TODO: Add your message handler code here and/or call default
	if (point.x < rect.right&&point.x>0 && point.y < rect.bottom&&point.y>0)
	{
		is_lbutton_down = 1;
		pl.drawSavePoint(&dc, point);
		Invalidate();
	}


	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	if (is_lbutton_down)
	{
		pl.drawSavePoint(&dc, point);
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	is_lbutton_down = 0;
	CWnd::OnLButtonUp(nFlags, point);
}


//BOOL CChildView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	//return CWnd::OnEraseBkgnd(pDC);
//	return true;
//}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	startp = point;
	is_rbutton_down = 1;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	endp = point;
	is_rbutton_down = 0;
	dc.Rectangle(CRect(startp, endp));
	flag = 1;
	
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}


//BOOL CChildView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	//return CWnd::OnEraseBkgnd(pDC);
//	return true;
//}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

//	return CWnd::OnEraseBkgnd(pDC);
	return true;
}
