// ChildView.cpp : CChildView Ŭ������ ����
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
	m_LineNum = 0;		//	�ʱ�ȭ
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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	for (int i = 0; i < m_LineNum + 1; i++) {
		m_Lines[i].Draw(&dc);
	}
		
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()�� ȣ������ ���ʽÿ�.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)		//	CPoint point  ���� ��ġ
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	// ���콺 �����Ͱ� ���� Ŭ���̾�Ʈ ���� ������ ������ ���� ��ǥ�� ����
	SetCapture();

	m_bLButtonDown = true;
	m_Lines[m_LineNum].m_start = point;
	
	CWnd::OnLButtonDown(nFlags, point);		
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	ReleaseCapture();
	
	m_bLButtonDown = false;
	m_Lines[m_LineNum].m_end = point;
	m_LineNum++;

	Invalidate();		//	 ��ȿ�ϴ�
	
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if (m_bLButtonDown) {
		m_Lines[m_LineNum].m_end = point;
		Invalidate();	
	}

	CWnd::OnMouseMove(nFlags, point);
}
