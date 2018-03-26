
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "t2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
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
	for (int i = 0; i <= count; i++)
	{
		plist[i].draw(&dc);
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	plist[count].orip = point;
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	plist[count].endp = point;
	count++;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mosp = point;
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i <= count; i++)
	{
		if ((plist[i].endp.x - mosp.x)*(plist[i].orip.x - mosp.x) <= 0 && (plist[i].endp.y - mosp.y)*(plist[i].orip.y - mosp.y) <= 0)
		{
			if (82 == nChar)
			{
				plist[i].brush.CreateSolidBrush(RGB(255, 0, 0)); break;
			}
			else if (71 == nChar)
			{
				plist[i].brush.CreateSolidBrush(RGB(0, 255, 0)); break;
			}
			else if (66 == nChar)
			{
				plist[i].brush.CreateSolidBrush(RGB(0, 0, 255)); break;
			}
			
		}
	}
Invalidate();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!需在for循环外面

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//// TODO: Add your message handler code here and/or call default
	//for (int i = 0; i <= count; i++)
	//{
	//	if ((plist[i].endp.x - mosp.x)*(plist[i].orip.x - mosp.x) <= 0 && (plist[i].endp.y - mosp.y)*(plist[i].orip.y - mosp.y) <= 0)
	//	{
	//		if ('r' == nChar)
	//		{
	//			plist[i].brush.CreateSolidBrush(RGB(255, 0, 0)); break;
	//		}
	//		else if ('g' == nChar)
	//		{
	//			plist[i].brush.CreateSolidBrush(RGB(0, 255, 0)); break;
	//		}
	//		else if ('b' == nChar)
	//		{
	//			plist[i].brush.CreateSolidBrush(RGB(0, 0, 255)); break;
	//		}

	//	}
	//}
	//Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
