// ChildView.cpp : CChildView 클래스의 구현
//

#include "stdafx.h"
#include "CircleFileTest.h"
#include "ChildView.h"
#include "MyCircle.h"

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
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_FILE_MYSAVE, &CChildView::OnFileMysave)
	ON_COMMAND(ID_FILE_MYLOAD, &CChildView::OnFileMyload)
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

	POSITION pos = m_circles.GetHeadPosition();
	while(pos!=NULL)
	{
		m_circles.GetNext(pos).Draw(&dc);
	}
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMyCircle temp;
	temp.m_pt = point;
	m_circles.AddTail(temp);
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnFileMysave()
{
	CFile file(_T("circle.dat"),CFile::modeWrite|CFile::modeCreate);
	
	CArchive ar(&file, CArchive::store);

	m_circles.Serialize(ar);

	/*
	
	int num = m_circles.GetCount();
	ar<<num;
	POSITION pos = m_circles.GetHeadPosition();
	while(pos!=NULL)
	{
		CMyCircle temp = m_circles.GetNext(pos);
		ar<<temp.m_pt;
	}
	*/
}

void CChildView::OnFileMyload()
{
	CFile file(_T("circle.dat"),CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	m_circles.RemoveAll();
	m_circles.Serialize(ar);
	/*
	int num;
	ar>>num;

	for(int i=0;i<num;i++)
	{
		CMyCircle temp;
		ar>>temp.m_pt;
		m_circles.AddTail(temp);

	}*/
	Invalidate();
}
