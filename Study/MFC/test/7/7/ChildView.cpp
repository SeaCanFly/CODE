
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "7.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	sp = { 0,0 };
	ep = { 100,100 };
	flag = 0;
	key = 0;
	dx = 10; dy = 10;
	mx = 0; my = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	
	// TODO: Add your message handler code here
	dc.Rectangle(CRect(sp, ep));
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case VK_UP:flag = 1; key = 1;
		break;
	case VK_DOWN:flag = 2; key = 1;
		break;
	case VK_LEFT:flag = 3; key = 1;
		break;
	case VK_RIGHT:flag = 4; key = 1;
		break;
	default:
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	mx = point.x - (sp.x + (ep.x - sp.x)/2);
	my = point.y - (sp.y + (ep.y - sp.y / 2));
	int x = (mx > 0) ? mx : (-mx);
	int y = (my > 0) ? my : (-my);
	if (y >= x)
	{
		b = my / mx;
	}
	else
	{
		b = mx / my;
	}
	flag = 5; key = 1;
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
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
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);
	if (flag == 1)//up
	{
		if (sp.y < 0)
		{
			dy = 10;
		}
		if (ep.y > rect.bottom)
		{
			dy = -10;
		}
		else if(key == 1)
		{
			dy = -10;
			key = 0;
		}
		sp.y += dy;
		ep.y += dy;
		Invalidate();
	}
	if (flag == 2)//down
	{
		if (sp.y < 0)
		{
			dy = 10;
		}
		if (ep.y > rect.bottom)
		{
			dy = -10;
		}
		else if(key == 1)
		{
			dy = 10;
			key = 0;
		}
		sp.y += dy;
		ep.y += dy;
		Invalidate();
	}
	if (flag == 3)//left
	{
		if (sp.x < 0)
		{
			dx = 10;
		}
		if (ep.x > rect.right)
		{
			dx = -10;
		}
		else if(key == 1)
		{
			dx = -10;
			key = 0;
		}
		sp.x += dx;
		ep.x += dx;
		Invalidate();
	}	
	if (flag == 4)//right
	{
		if (sp.x < 0)
		{
			dx = 10;
		}
		if (ep.x > rect.right)
		{
			dx = -10;
		}
		else if(key == 1)
		{
			dx = 10;
			key = 0;
		}
		sp.x += dx;
		ep.x += dx;
		Invalidate();
	}
	if (flag == 5)
	{
		if (sp.y < 0)
		{
			dy = b*10;
			dy = (dy > 0) ? dy : (-dy);
		}
		if (ep.y > rect.bottom)
		{
			dy = b*10;
			dy = (dy > 0) ? (-dy) : dy;
		}
		if (ep.x > rect.right)
		{
			dx = 10;
			dx = (dx > 0) ? (-dx) : dx;
		}
		if (sp.x < 0)
		{
			dx = 10;
			dx = (dx > 0) ? dx : (-dx);
		}
		else if(key == 1)
		{
			dx = 10;
			dy = b*10;
			key = 0;
		}
		sp.x += dx;
		sp.y += dy;
		ep.x += dx;
		ep.y += dy;
		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}
