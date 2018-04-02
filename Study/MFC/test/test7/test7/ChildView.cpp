
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test7.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	startp = { 0,0 };
	endp = { 100,100 };
	flag = 0;
	dx = 10; dy = 10;
	mx = 0; my = 0;
	key = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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

	// TODO: Add your message handler code here
	dc.Rectangle(startp.x, startp.y, endp.x, endp.y);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (VK_UP == nChar)
	{
		flag = 1;
		key = 1;
	}
	if (VK_DOWN == nChar)
	{
		flag = 2;
		key = 1;
	}
	if (VK_LEFT == nChar)
	{
		flag = 3;
		key = 1;
	}
	if (VK_RIGHT == nChar)
	{
		flag = 4;
		key = 1;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(0, 30, NULL);
	// TODO:  Add your specialized creation code here

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CRect rect;
	GetClientRect(&rect);
	// TODO: Add your message handler code here and/or call default
	if (0 == nIDEvent)
	{
		if (flag == 1)
		{

			if (startp.y < 0)
			{
				dy = 10;
			}
			else if (endp.y > rect.bottom)
			{
				dy = -10;
			}
			else if (key == 1)
			{
				dy = -10;
				key = 0;
			}
			startp.y += dy;
			endp.y += dy;
			Invalidate();
		}
		else if (flag == 2)
		{
			if (startp.y < 0)
			{
				dy = 10;
			}
			else if (endp.y > rect.bottom)
			{
				dy = -10;
			}
			else if (key == 1)
			{
				dy = 10;
				key = 0;
			}
			startp.y += dy;
			endp.y += dy;
			Invalidate();
		}
		else if (flag == 3)
		{
			if (startp.x < 0)
			{
				dx = 10;
			}

			else if (endp.x > rect.right)
			{
				dx = -10;
			}
			else if (key == 1)
			{
				dx = -10;
				key = 0;
			}
			startp.x += dx;
			endp.x += dx;
			Invalidate();
		}
		else if (flag == 4)
		{
			if (startp.x < 0)
			{
				dx = 10;
			}
			else if (endp.x > rect.right)
			{
				dx = -10;
			}
			else if (key == 1)
			{
				dx = 10;
				key = 0;
			}
			startp.x += dx;
			endp.x += dx;
			Invalidate();
		}
		else if (flag == 5)
		{
			if (startp.x < 0)
			{
				dx = mx / 50;
				dx = (dx >= 0) ? dx : (-dx);
			}
			if (startp.y < 0)
			{
				dy = my / 50;
				dy = (dy >= 0) ? dy : (-dy);
			}
			if (endp.x > rect.right)
			{
				dx = mx / 50;
				dx = (dx >= 0) ? (-dx) : dx;
			}
			if (endp.y > rect.bottom)
			{
				dy = my / 50;
				dy = (dy >= 0) ? (-dy) : dy;
			}
			else if (key == 1)
			{
				dx = mx / 50;
				dy = my / 50;
				key = 0;
			}
			startp.x += dx;
			startp.y += dy;
			endp.x += dx;
			endp.y += dy;
			Invalidate();
		}

	}

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mx = point.x - (startp.x + (endp.x - startp.x));
	my = point.y - (startp.y + (endp.y - startp.y));
	flag = 5; key = 1;
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}
