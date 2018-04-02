
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
	flag = 0;
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
//	ON_WM_ERASEBKGND()
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
	for (int i = 0; i < count; i++)
	{
		plist[i].draw(&dc);
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	is_lbutton_down = 1;
	mousp = point;
	if (flag == 1)
	{
		plist[select].brush.CreateSolidBrush(RGB(255, 0, 0));
		plist[select].draw(&dc);
		Invalidate();
	}
	if (flag == 0)
	{
		plist[count].startp = point;
	}

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	is_lbutton_down = 0;
	if (flag == 0)
	{
		plist[count].endp = point;
		count++;
	}
	if (flag == 1)
	{
		flag = 0;
	}
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		for (int i = count-1 ; i >= 0; i--)
		{
			if ((mousp.x - plist[i].startp.x)*(mousp.x - plist[i].endp.x) < 0 &&
				(mousp.y - plist[i].startp.y)*(mousp.y - plist[i].endp.y) < 0&&is_lbutton_down)
			{
				select = i; flag = 1; break;
			}
		}
	if (flag == 1 && is_lbutton_down == 1)
	{
		int mx = (point.x - mousp.x);
		int my = (point.y - mousp.y);
		plist[select].startp.x += mx;
		plist[select].startp.y += my;
		plist[select].endp.x += mx;
		plist[select].endp.y += my;
		plist[select].brush.CreateSolidBrush(RGB(255, 0, 0));
		mousp = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


//BOOL CChildView::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	//return CWnd::OnEraseBkgnd(pDC);
//	return true;
//}
