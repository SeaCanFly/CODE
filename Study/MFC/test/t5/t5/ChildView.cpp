
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "t5.h"
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
	ON_WM_SIZE()
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
	bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmapinfo;
	bitmap.GetBitmap(&bmapinfo);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);

	memdc.SelectObject(&bitmap);
	float scale = 1.0;
	dc.SetStretchBltMode(HALFTONE);
	if ((bmapinfo.bmWidth <= rect.Width()) && (bmapinfo.bmHeight <= rect.Height()))
	{
		dc.StretchBlt((rect.Width() / 2 - bmapinfo.bmWidth*scale / 2), 0, bmapinfo.bmWidth*scale, bmapinfo.bmHeight*scale,
			&memdc, 0, 0, bmapinfo.bmWidth, bmapinfo.bmHeight, SRCCOPY);
	}
	if (bmapinfo.bmWidth > rect.Width()||bmapinfo.bmHeight > rect.Height())
	{
		float wid = (float)rect.Width() / bmapinfo.bmWidth;
		float hei = (float)rect.Height() / bmapinfo.bmHeight;
		scale = (wid >= hei) ? hei : wid;
		dc.StretchBlt((rect.Width() / 2 - bmapinfo.bmWidth*scale / 2), 0, bmapinfo.bmWidth*scale, bmapinfo.bmHeight*scale,
			&memdc, 0, 0, bmapinfo.bmWidth, bmapinfo.bmHeight, SRCCOPY);
	}
	//dc.BitBlt((rect.Width()/2-bmapinfo.bmWidth/2), 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	//h = cy; w = cx;
	// TODO: Add your message handler code here
}
