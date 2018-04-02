// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "TypingTest.h"
#include "ChildView.h"
#include ".\childview.h"

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
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);

	dc.DrawText(m_str, &rect, DT_LEFT);

}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnChar(nChar, nRepCnt, nFlags);

	m_str += (TCHAR) nChar;
	Invalidate();

}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);

	CFile file;
	CFileException e;
	if(!file.Open(_T("testString.dat"), CFile::modeCreate|CFile::modeWrite, &e))
	{
		e.ReportError();	
		return;
	}

	CArchive ar(&file, CArchive::store);
	ar<<m_str;
    

}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnRButtonDown(nFlags, point);

	CFile file;
	CFileException e;
	if(!file.Open(_T("testString.dat"), CFile::modeRead, &e))
	{
		e.ReportError();	
		return;
	}

	CArchive ar(&file, CArchive::load);
	ar>>m_str;
	Invalidate();

}
