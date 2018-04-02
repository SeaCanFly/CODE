
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
	is_lbutton_down = 0;
	count = 0;
	s = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
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
	CBitmap membitmap;
	membitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(&membitmap);
	memdc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	// TODO: Add your message handler code here
	for (int i = 0; i < count + 1; i++)
	{
		plist[i].draw(&memdc);
	}
	plist[s].color(&memdc);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	/*if (nFlags&MK_LBUTTON)
	{*/
	is_lbutton_down = 1;
	flag = 0;
	for (int i = count-1; i >= 0; i--)
	{
		if ((point.x -plist[i].spos.x)*(point.x -plist[i].epos.x)<0 &&
			(point.y -plist[i].spos.y) * (point.y -plist[i].epos.y)<0)
		{
			s=i; flag = 1; break;
		}
	}
	if (flag == 1)
	{
		plist[s].color(&dc);
		orip = point;
	}
	if (flag == 0)
	{
		plist[count].spos = point;
	}
	/*}*/
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	if ((is_lbutton_down == 1) && (flag == 0))
	{
		plist[count].epos = point;
		Invalidate();
	}
	if (is_lbutton_down&&flag == 1)
	{

		plist[s].spos.x = plist[s].spos.x + point.x - orip.x;
		plist[s].spos.y = plist[s].spos.y + point.y - orip.y;
		plist[s].epos.x += point.x - orip.x;
		plist[s].epos.y += point.y - orip.y;
		orip = point;
		/*plist[s].color(&dc);*/
		/*plist[s].draw(&dc);*/
		InvalidateRect(NULL);
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (flag == 0)
	{
		plist[count].epos = point;
		is_lbutton_down = 0;
		count++;
	}
	if (flag)
	{
		Invalidate();
		is_lbutton_down = 0;
		flag = 0;
	}

	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
