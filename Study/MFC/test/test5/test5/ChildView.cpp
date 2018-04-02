
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test5.h"
#include "ChildView.h"
#include "Resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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
	// TODO: Add your message handler code here
	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	BITMAP bminfo;
	bitmap.GetBitmap(&bminfo);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	memdc.SelectObject(&bitmap);
	float scale = 1.0;
	dc.SetStretchBltMode(HALFTONE);
	if (bminfo.bmWidth <= rect.Width() && bminfo.bmHeight <= rect.Height())
	{
		dc.StretchBlt((rect.Width() / 2 - bminfo.bmWidth*scale / 2), 0, bminfo.bmWidth*scale, bminfo.bmHeight*scale,
			&memdc, 0, 0, bminfo.bmWidth, bminfo.bmHeight, SRCCOPY);
	}
	else if (bminfo.bmWidth > rect.Width() || bminfo.bmHeight > rect.Height())
	{
		float mw = (float)rect.Width() / bminfo.bmWidth;
		float mh = (float)rect.Height() / bminfo.bmHeight;
		scale = (mw >= mh) ? mh : mw;
		dc.StretchBlt((rect.Width() / 2 - bminfo.bmWidth*scale / 2), 0, bminfo.bmWidth*scale, bminfo.bmHeight*scale,
			&memdc, 0, 0, bminfo.bmWidth, bminfo.bmHeight, SRCCOPY);
	}
	// Do not call CWnd::OnPaint() for painting messages
}

