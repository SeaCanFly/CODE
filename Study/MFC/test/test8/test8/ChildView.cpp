
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "test8.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	count = 0;
	a = 9;
	t = 1;

	flag = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	//	ON_WM_SYSKEYUP()
	ON_WM_TIMER()
	ON_WM_KEYUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
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
	//dc.Ellipse(0, 0, 1420, 696);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap membmap;
	membmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(&membmap);
	memdc.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));
	for (int i = 0; i < count; i++)
	{
		memdc.Ellipse(CRect(plist[i].startp, plist[i].endp));
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CClientDC dc(this);
	GetClientRect(&rect);
	flag = 0;
	Invalidate();
	// TODO: Add your message handler code here and/or call default
	if (VK_SPACE == nChar)
	{
		plist[count].v = 0;
		plist[count].startp.x = rect.Width() / 2 - 20;
		plist[count].startp.y = rect.Height() / 2 - 20;
		plist[count].endp.x = rect.Width() / 2 + 20;
		plist[count].endp.y = rect.Height() / 2 + 20;
	}
	dis = (rect.right - ((count + 1) * 40)) / 2;
	for (int i = 0; i <= count; i++)
	{

		plist[i].v = 0 + i * 5;
		plist[i].startp.x = dis + i * 40;
		plist[i].startp.y = rect.Height() / 2 - 20;
		plist[i].endp.x = dis + i * 40 + 40;
		plist[i].endp.y = rect.Height() / 2 + 20;
	}

	/*for (int i = 0; i <= count; i++)
	{
		plist[i].v = 0 + i * 5;
		plist[i].startp.x = (rect.Width() - i * 80) / 2 - 20;
		plist[i].startp.y = (rect.Height()) / 2 - 20;
		plist[i].endp.x = (rect.Width() - i * 80) / 2 + 20;
		plist[i].endp.y = (rect.Height()) / 2 + 20;

	}*/

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


//void CChildView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	
//	CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
//}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i < count; i++)
	{
		if (i == nIDEvent&&flag == 1)
		{
			plist[i].v = plist[i].v + a*t;
			plist[i].startp.y += plist[i].v*t;
			plist[i].endp.y += plist[i].v*t;
			if (plist[i].endp.y > rect.bottom)
			{
				plist[i].startp.y = rect.bottom - 40;
				plist[i].endp.y = rect.bottom;
				plist[i].v = -plist[i].v * 4 / 5;
			}
			Invalidate();
		}

	}
	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	// TODO: Add your message handler code here and/or call default
	if (VK_SPACE == nChar)
	{
		for (int i = 0; i <= count; i++)
		{
			SetTimer(i, 30, NULL);
		}
		count++;
		flag = 1;

	}

	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}
