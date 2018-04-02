
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "t4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
	orip = { 201, 51 };//¥Û¿®∫≈
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
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
	dc.Rectangle(200, 50, 900, 300);
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	if (nChar == 0x0d)
	{
		/*str.Empty();*/
		count++;
		orip.y += tm.tmHeight;
	}
	else if (nChar == 0x08)
	{
		if (str[count] ==_T("")&&count!=0)
		{
			count--;
			orip.y -= tm.tmHeight;
			
		
		}
		else {
			COLORREF oriclr = dc.SetTextColor(dc.GetBkColor());
			dc.TextOutW(orip.x, orip.y, str[count]);
			str[count] = str[count].Left(str[count].GetLength() - 1);
			dc.SetTextColor(oriclr);
			ShowCaret();
		}

	}
	else
	{
		str[count] = str[count] + (TCHAR)nChar;
	}
	CSize swid = dc.GetTextExtent(str[count]);
	CPoint pt;
	pt.x = orip.x + swid.cx;
	pt.y = orip.y;
	SetCaretPos(pt);
	dc.TextOut(orip.x, orip.y, str[count]);
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar)
	{
		CreateSolidCaret(1, 20);
		SetCaretPos(orip);
		ShowCaret();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
