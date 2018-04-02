// ChildView.cpp : CChildView Ŭ������ ����
//

#include "stdafx.h"
#include "CListTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_RButton = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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

	POSITION ppp = m_pt.GetHeadPosition();
	while(ppp != NULL)
	{
		CPoint pt = m_pt.GetAt(ppp);
		dc.SetPixelV(pt, RGB(0, 0, 0));
		m_pt.GetNext(ppp);
	}

	if(m_RButton == true)
	{
		dc.Rectangle(m_st.x, m_st.y, m_ed.x, m_ed.y);
	}
	
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(nFlags == MK_LBUTTON)
	{
		m_pt.AddTail(point);
		Invalidate();
	}
	else if(nFlags == MK_RBUTTON)
	{
		m_ed = point;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_st = point;
	m_ed = point;
	m_RButton = true;

	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_ed = point;
	m_RButton = false;

	POSITION ppp = m_pt.GetHeadPosition();
	while(ppp != NULL)
	{
		POSITION cur = ppp;		
		CPoint pt = m_pt.GetAt(ppp);
		m_pt.GetNext(ppp);

		if(m_st.x < pt.x && pt.x < m_ed.x && m_st.y < pt.y && pt.y < m_ed.y)
		{
			m_pt.RemoveAt(cur);
		}
	}

	Invalidate();

	CWnd::OnRButtonUp(nFlags, point);
}
