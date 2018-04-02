
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCApplication6.h"
#include "ChildView.h"
#include "MyDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dlg = 0;
	vsum = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
ON_WM_CREATE()
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
	dc.TextOutW(1, 1, vstr);
	CString s;
	s.Format(_T("%d"), vsum);
	dc.TextOutW(100, 100, s);
	// Do not call CWnd::OnPaint() for painting messages
}



//void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CWnd::OnLButtonDown(nFlags, point);
//}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
if (dlg == 0)
	{
	dlg = new MyDialog;
	dlg->Create(IDD_DIALOG1,this);
	dlg->ShowWindow(1);
	UpdateData(1);
	dlg->cview = this;
	}
	
	// TODO:  Add your specialized creation code here

	return 0;
}
