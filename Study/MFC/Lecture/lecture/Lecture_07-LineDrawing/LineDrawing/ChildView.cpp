// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "LineDrawing.h"
#include "ChildView.h"
#include "MyLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bLButtonDown = false;
	m_LineNum = 0;		//	초기화
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

	for (int i = 0; i < m_LineNum + 1; i++) {
		m_Lines[i].Draw(&dc);
	}
		
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)		//	CPoint point  눌린 위치
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// 마우스 포인터가 현재 클라이언트 영역 밖으로 나갔을 때도 좌표를 얻어옴
	SetCapture();

	m_bLButtonDown = true;
	m_Lines[m_LineNum].m_start = point;
	
	CWnd::OnLButtonDown(nFlags, point);		
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	ReleaseCapture();
	
	m_bLButtonDown = false;
	m_Lines[m_LineNum].m_end = point;
	m_LineNum++;

	Invalidate();		//	 유효하다
	
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bLButtonDown) {
		m_Lines[m_LineNum].m_end = point;
		Invalidate();	
	}

	CWnd::OnMouseMove(nFlags, point);
}
