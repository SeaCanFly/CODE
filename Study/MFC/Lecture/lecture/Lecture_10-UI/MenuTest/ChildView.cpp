// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MenuTest.h"
#include "ChildView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = RGB(0, 0, 0);
	m_bDrawCir = false;
	m_bDrawRect = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CChildView::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CChildView::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CChildView::OnUpdateColorRed)
	ON_COMMAND(ID_SELECT_CIRCLE, &CChildView::OnSelectCircle)
	ON_COMMAND(ID_SELECT_RECTANGLE, &CChildView::OnSelectRectangle)
	ON_WM_MOUSEMOVE()
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
	CBrush brush(m_color);
	dc.SelectObject(&brush);
	if (m_bDrawCir)
		dc.Ellipse(100, 100, 300, 300);
	if (m_bDrawRect)
		dc.Rectangle(100, 100, 300, 300);
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnContextMenu(CWnd *pWnd, CPoint point)
{
//	AfxMessageBox(_T("Context Menu"));
	
	CMenu * pMainMenu = AfxGetMainWnd()->GetMenu();								// 메인 프레임에 존재하는 메뉴 가져오기
	CMenu * pMenu = pMainMenu->GetSubMenu(4);									// '1'번째 메뉴의 서브메뉴를 보여줌
	pMenu->	TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd());	// 누르는 위치에 왼쪽 맞춤으로 화면에 나타냄
/*
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);

	CMenu* pMenu = menu.GetSubMenu(4); 

	pMenu->TrackPopupMenu(
		TPM_LEFTALIGN|TPM_RIGHTBUTTON,
		point.x, point.y, AfxGetMainWnd()); 
*/
}

void CChildView::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 0, 255);
	Invalidate();
}


void CChildView::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(0, 255, 0);
	Invalidate();
}


void CChildView::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_color = RGB(255, 0, 0);
	Invalidate();
}


void CChildView::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_color == RGB(0, 0, 255))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_color == RGB(0, 255, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_color == RGB(255, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}

void CChildView::OnSelectCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bDrawRect = false;
	m_bDrawCir = true;
	
	Invalidate();
}


void CChildView::OnSelectRectangle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bDrawRect = true;
	m_bDrawCir = false;

	Invalidate();
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->m_wndStatusBar.SetPaneText(1, _T("HaHa"));
	
	CString str;
	str.Format(_T("Mouse Position(%d, %d)"), point.x, point.y);
	pMain->m_wndStatusBar.SetPaneText(2, str);
	
	CWnd::OnMouseMove(nFlags, point);
}
