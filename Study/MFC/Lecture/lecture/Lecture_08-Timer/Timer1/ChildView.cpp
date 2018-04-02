// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "Timer1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pt = CPoint(100,100);
	m_color = RGB(255, 0, 0);
	m_dy = 10;

	m_py = 100;
	m_vy = 0;
	m_ay = 0;

	m_bChangeColor = true;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
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

	CBrush brush(m_color);
	dc.SelectObject(&brush);
	
	// 상하로 움직이는 원을 그림
	dc.Ellipse(m_pt.x, m_pt.y, m_pt.x + 50, m_pt.y + 50);
	
	// 중력에 의해 뜅기는 원을 그림
	CPoint pt(200, (int)m_py);
	dc.Ellipse(pt.x, pt.y, pt.x + 50, pt.y + 50);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	SetTimer(0, 33, NULL);		// 타이머 0
	SetTimer(1, 500, NULL);		// 타이머 1

	return 0;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 오른쪽으로 원 움직이기
	
	if(nIDEvent == 0)					// 타이머0일때
	{
		CRect rect;
		GetClientRect(&rect);
		if(m_pt.y + 50 > rect.bottom)	// 원의 아래쪽 끝이 화면의 아래쪽 최대 좌표값보다 클 경우
			m_dy = -10;					// y좌표값의 변위를 -10으로 바꾼다
		if(m_pt.y < 0)					
			m_dy = 10;					// m_dy : displacement

		m_pt.y += m_dy;					// y좌표에 변위를 더함
		Invalidate(); 
	}

	if (nIDEvent == 1 && m_bChangeColor)					//타이머1일때
	{
		m_color = RGB(rand()%256, rand()%256, rand()%256);	//칼라값 랜덤
		Invalidate();										//그림을 다시 그림
	}


	if(nIDEvent == 0)
	{

		CRect rect;
		GetClientRect(&rect);

		float dt = 0.03f;	// 30 millisecond
		//1. update force f
		float fy = 300;
		//2. update acceleration a
		m_ay = fy;
		//3. update velocity v
		m_vy = m_vy + m_ay*dt;
		//4.update position p
		m_py = m_py + m_vy*dt;

		// bouncing when reaching the wall
		if (m_py+50 > rect.bottom) 
		{
			m_py = (float)rect.bottom - 50;
			m_vy = -m_vy * 0.8f;

		}
		Invalidate(); 
	}

	CWnd::OnTimer(nIDEvent);
}
