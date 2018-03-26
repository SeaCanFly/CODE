
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "HW2_WangYiSen.h"
#include "ChildView.h"
#include "MyShape.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_lbutton_down = false;
	m_rbutton_down = false;
	count = 0;
	count_pixel = 0;
	index = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
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
	if (!memDC.m_hDC)
	{
		GetClientRect(&rect);
		memDC.CreateCompatibleDC(&dc);
		CBitmap Membitmap;
		Membitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		CBitmap *pOldBit = memDC.SelectObject(&Membitmap);
		memDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

		for (int i = 0; i < count + 1; i++)
		{
			rect_list[i].Draw(&memDC);
			cir_list[i].Draw(&memDC);
		}
		for (int i = 0; i < index + 1; i++)
		{
			pixel_list[i].DrawRgn(&memDC, pixel_list[i], i, cp[i]);
		}
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		Membitmap.DeleteObject();
		memDC.DeleteDC();
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	SetCapture();
	cp[index] = count_pixel;
	pixel_list[index].DrawRgn(&dc, pixel_list[index], index, count_pixel);
	index++;
	count_pixel = 0;
	m_lbutton_down = true;
	rect_list[count].pstart = point;
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	m_lbutton_down = false;
	rect_list[count].pend = point;
	count++;
	rect_list[count].Draw(&dc);

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	pixel_list[index].pixel[count_pixel] = point;
	count_pixel++;
	dc.Ellipse(point.x - 2, point.y - 2, point.x + 2, point.y + 2);
	CWnd::OnMButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();
	m_rbutton_down = true;
	cir_list[count].pstart = point;
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	m_rbutton_down = false;
	cir_list[count].pend = point;
	count++;
	cir_list[count].Draw(&dc);

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	if (m_lbutton_down)
	{
		rect_list[count].pend = point;
		Invalidate();
	}
	if (m_rbutton_down)
	{
		cir_list[count].pend = point;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
