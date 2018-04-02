
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	orip = { 301, 101 };
	count = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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
	dc.Rectangle(300, 100, 900, 500);
	/*for (int i = 0; i < count; i++)
	{
		dc.TextOutW(orip.x, orip.y, str[i]);
	}*/
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar)
	{
		CreateSolidCaret(2, 20);
		SetCaretPos(orip);
		ShowCaret();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	// TODO: Add your message handler code here and/or call default
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	if (VK_RETURN == nChar)
	{
		HideCaret();
		orip.y += tm.tmHeight;
		ShowCaret();
		count++;
		//Invalidate();
	}
	if (VK_BACK == nChar)
	{
		if (str[count] == _T("") && count != 0)
		{
			//DestroyCaret();
			HideCaret();
			count--;
			orip.y -= tm.tmHeight;
			ShowCaret();
			//Invalidate();
			//ShowCaret();
		}
		else
		{
			HideCaret();
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			dc.TextOutW(orip.x, orip.y, str[count]);
			str[count] = str[count].Left(str[count].GetLength() - 1);
			dc.SetTextColor(clr);
			ShowCaret();
		}

	}
	else
	{
		str[count] += (TCHAR)nChar;
	}
	CSize word_width;
	word_width = dc.GetTextExtent(str[count]);
	CPoint pt;
	pt.x = orip.x + word_width.cx;
	pt.y = orip.y;
	SetCaretPos(pt);
	dc.TextOutW(orip.x, orip.y, str[count]);
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}
