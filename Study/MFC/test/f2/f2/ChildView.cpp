
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "f2.h"
#include "ChildView.h"

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
	ON_COMMAND(ID_FILE_NEW, &CChildView::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_LOAD, &CChildView::OnFileLoad)
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
	POSITION pos = pl.GetHeadPosition();
	while (pos)
	{
		CPoint pt = pl.GetAt(pos);
		dc.Rectangle(pt.x - 20, pt.y - 20, pt.x + 20, pt.y + 20);
		pl.GetNext(pos);
	}
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnFileNew()
{
	pl.RemoveAll();
	Invalidate();
	// TODO: Add your command handler code here
}


void CChildView::OnFileOpen()
{
	
	// TODO: Add your command handler code here
}


void CChildView::OnFileSave()
{
	CFile file;
	CFileException e;
	if (file.Open(_T("C.dat"), CFile::modeCreate |CFile::modeReadWrite, &e) == 0)
	{
		e.ReportError();
		return;
	}
	CArchive ar(&file, CArchive::store);
	pl.Serialize(ar);
	ar.Close();
	file.Close();
	// TODO: Add your command handler code here
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	pl.AddTail(point);
	Invalidate();
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnFileLoad()
{
	pl.RemoveAll();
	CFile file;
	CFileException e;
	if (file.Open(_T("C.dat"), CFile::modeReadWrite, &e) == 0)
	{
		e.ReportError();
		return;
	}
	CArchive ar(&file, CArchive::load);
	pl.Serialize(ar);
	ar.Close();
	file.Close();
	Invalidate();
	// TODO: Add your command handler code here
}
