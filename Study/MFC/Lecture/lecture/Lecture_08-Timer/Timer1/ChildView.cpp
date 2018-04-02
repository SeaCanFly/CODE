// ChildView.cpp : CChildView Ŭ������ ����
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



// CChildView �޽��� ó����

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
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

	CBrush brush(m_color);
	dc.SelectObject(&brush);
	
	// ���Ϸ� �����̴� ���� �׸�
	dc.Ellipse(m_pt.x, m_pt.y, m_pt.x + 50, m_pt.y + 50);
	
	// �߷¿� ���� �ޱ�� ���� �׸�
	CPoint pt(200, (int)m_py);
	dc.Ellipse(pt.x, pt.y, pt.x + 50, pt.y + 50);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	SetTimer(0, 33, NULL);		// Ÿ�̸� 0
	SetTimer(1, 500, NULL);		// Ÿ�̸� 1

	return 0;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	// ���������� �� �����̱�
	
	if(nIDEvent == 0)					// Ÿ�̸�0�϶�
	{
		CRect rect;
		GetClientRect(&rect);
		if(m_pt.y + 50 > rect.bottom)	// ���� �Ʒ��� ���� ȭ���� �Ʒ��� �ִ� ��ǥ������ Ŭ ���
			m_dy = -10;					// y��ǥ���� ������ -10���� �ٲ۴�
		if(m_pt.y < 0)					
			m_dy = 10;					// m_dy : displacement

		m_pt.y += m_dy;					// y��ǥ�� ������ ����
		Invalidate(); 
	}

	if (nIDEvent == 1 && m_bChangeColor)					//Ÿ�̸�1�϶�
	{
		m_color = RGB(rand()%256, rand()%256, rand()%256);	//Į�� ����
		Invalidate();										//�׸��� �ٽ� �׸�
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
