// ChildView.cpp : CChildView 클래스의 구현


#include "stdafx.h"
#include "CFileTest.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	CFile file(_T("test.txt"), CFile::modeCreate|CFile::modeWrite);

	int a = 30;
	int b = 20;

	file.Write(&a, sizeof(a));
	file.Write(&b, sizeof(b));

	file.Close();

	CFile file2;
	CFileException e;

	if( !file2.Open(_T("test.txt"), CFile::modeRead, &e))
	{
		e.ReportError();
		return;
	};

	int a2, b2;
	file2.Read(&a2, sizeof(a2));
	file2.Read(&b2, sizeof(b2));

	CString str;
	str.Format(_T("a=%d b=%d"), a2, b2);
	AfxMessageBox(str);

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//file writing
	
	
	try
	{
		CFile file(_T("test.dat"), CFile::modeWrite|CFile::modeCreate);
		
		//저장변수들
		int a = 30;
		float b = 20.0f;	
		
		file.Write(&a, sizeof(a));	
		file.Write(&b, sizeof(b));
	}

	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//file reading
	try
	{
		CFile file(_T("test.dat"), CFile::modeRead);
		
		int a;
		float b;

		file.Read(&a, sizeof(a));
		file.Read(&b, sizeof(b));

		CString str;
		str.Format(_T("a=%d, b=%.2f"), a, b);
		AfxMessageBox(str);
	}

	catch(CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

	CWnd::OnRButtonDown(nFlags, point);
}
