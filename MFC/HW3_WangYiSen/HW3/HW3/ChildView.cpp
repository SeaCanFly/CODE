
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "HW3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	mx = 0; my = 0;
	key = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CChildView::OnColorBlack)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_RECTANGLE, &CChildView::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CChildView::OnEllipse)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CChildView::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CChildView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_RECTANGLE, &CChildView::OnUpdateRectangle)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MOVEERASER, &CChildView::OnMoveeraser)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_MOVEERASER, &CChildView::OnUpdateMoveeraser)
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

	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap membp;
	membp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	memdc.SelectObject(&membp);
	memdc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	// TODO: Add your message handler code here
	
	line.showLine(&memdc);
	eraser.doErase(&memdc,line);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnColorRed()
{
	// TODO: Add your command handler code here
	pt.setColor(RGB(255, 0, 0));
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: Add your command handler code here
	pt.setColor(RGB(0, 255, 0));
	Invalidate();
}


void CChildView::OnColorBlue()
{
	pt.setColor(RGB(0, 0, 255));
	Invalidate();
	// TODO: Add your command handler code here
}


void CChildView::OnColorBlack()
{
	pt.setColor(RGB(0, 0, 0));
	Invalidate();
	// TODO: Add your command handler code here
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	// TODO: Add your message handler code here and/or call default
	pt.setPoint(point);
	line.savePoint(pt);
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags == VK_LBUTTON)
	{
		pt.setPoint(point);
		line.savePoint(pt);
		Invalidate();
	}
	if (nFlags == VK_RBUTTON)
	{
		eraser.setPosition(startp, point);
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


void CChildView::OnRectangle()
{
	pt.setRect(1);
	// TODO: Add your command handler code here
}


void CChildView::OnEllipse()
{
	pt.setRect(0);
	// TODO: Add your command handler code here
}


void CChildView::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	
	pCmdUI->SetCheck(pt.getColor() == RGB(0, 0, 0));
	// TODO: Add your command update UI handler code here
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pt.getColor() == RGB(0, 0, 255));
	// TODO: Add your command update UI handler code here
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pt.getColor() == RGB(0, 255, 0));
	// TODO: Add your command update UI handler code here
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pt.getColor() == RGB(255, 0, 0));
	// TODO: Add your command update UI handler code here
}


void CChildView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(pt.getRect() == 0);
}


void CChildView::OnUpdateRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(pt.getRect() == 1);
	// TODO: Add your command update UI handler code here
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	eraser.delEraser();
	startp = point;
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnMoveeraser()
{
	mx = 0; my = 0;
	if (0==key)
	{
		SetTimer(0, 30, NULL);
		key = 1;
	}
	else
	{
		KillTimer(0);
		key = 0;
	}
	// TODO: Add your command handler code here
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		CRect crect,erect;
		GetClientRect(&crect);
		erect = eraser.getPositon();
		if (erect.right > crect.right)
		{
			mx = -10; my = 0;
		}
		else if (erect.bottom > crect.bottom)
		{
			mx = 0; my = -10;
		}
		else if (erect.left < 0)
		{
			mx = 10; my = 0;
		}
		else if (erect.top < 0)
		{
			mx = 0; my = 10;
		}
		eraser.movePositon(mx, my);
		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_UP)
	{
		mx = 0; my = -10;
	}
	else if (nChar == VK_DOWN)
	{
		mx = 0; my = 10;
	}
	else if (nChar == VK_LEFT)
	{
		mx = -10; my = 0;
	}
	else if (nChar == VK_RIGHT)
	{
		mx = 10; my = 0;
	}
	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnUpdateMoveeraser(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(key==1);
	// TODO: Add your command update UI handler code here
}
