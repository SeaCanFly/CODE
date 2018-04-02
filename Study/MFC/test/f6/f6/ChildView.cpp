
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "f6.h"
#include "ChildView.h"
#include "MyDialog.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	dlg = 0;
	sum = 0;
	vstr = "";
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
	dlg = new MyDialog;
	dlg->Create(IDD_DIALOG1);
	dlg->ShowWindow(1);
	dlg->cv = this;
	UpdateData();
	// TODO:  Add your specialized creation code here

	return 0;
}
