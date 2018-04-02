
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "HW4.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	b_start = 0;
	nshape = -1;
	r = 0;
	cur = 0;
	mx = 0; my = 0;
	d = 300.0;
	right = -1; left = -1;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(100, onStart)
	ON_BN_CLICKED(101, onPause)
	ON_BN_CLICKED(102, onSave)
	ON_BN_CLICKED(103, onLoad)
	ON_BN_CLICKED(104, onClean)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(rect);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	CBitmap membp;
	membp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	memdc.SelectObject(&membp);
	memdc.FillSolidRect(CRect(0, 0, rect.Width(), rect.Height()), RGB(255, 255, 255));
	// TODO: Add your message handler code here


	POSITION pos = list.GetHeadPosition();
	if (pos == 0)
	{
		memdc.FillSolidRect(CRect(0, 0, rect.Width(), rect.Height()), RGB(255, 255, 255));
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
		return;
	}
	if (b_start == 1)
	{

		int max = list.GetCount();
		scrollbar.SetScrollRange(0, max - 1);
		if (cur == max - 1)
		{	mx = 0;
			my = 0;
		}
		if (right > 0||left>0)
		{
			d = 50;
		}
		if (cur < max-1)
		{
			POSITION cpos = list.FindIndex(cur);
			move = list.GetAt(cpos);
			POSITION npos = list.FindIndex(cur + 1);
			double epx = list.GetAt(npos).x;
			double epy = list.GetAt(npos).y;
			mx = (epx - move.x);
			my = (epy - move.y);
			double s = my / mx;
			mx = mx / d;
			my = s*mx;
			move.mb_shape = list.GetAt(cpos).mb_shape;
			if (list.GetAt(npos).mb_shape != move.mb_shape)
			{
				if (list.GetAt(npos).mb_shape == 0)
				{
					nshape = 0;
					r = 0;
				}
				else
				{
					nshape = 1;
					r = 100;
				}
			}
			else
			{
				nshape = -1;
				r = 0;
			}
		}
		while (d)
		{
			move.x += mx;
			move.y += my;
			memdc.FillSolidRect(CRect(0, 0, rect.Width(), rect.Height()), RGB(255, 255, 255));
			POSITION tpos = list.GetHeadPosition();
			memdc.MoveTo(list.GetAt(tpos).p);
			while (tpos != 0)
			{

				Shape temp = list.GetAt(tpos);
				CPen  pen(PS_DASH, 1, RGB(0, 0, 0));
				CPen* oldpen = memdc.SelectObject(&pen);
				memdc.LineTo(temp.p);
				memdc.SelectObject(oldpen);
				list.GetNext(tpos);
			}
			if (nshape == 1)
			{
				if (r >= 0)
				{
					r--;
				}
				CRect trect(move.x - 20, move.y - 20, move.x + 20, move.y + 20);
				CPoint temp(r, r);
				memdc.RoundRect(trect, temp);
			}
			else if (nshape == 0)
			{
				if (r <= 100)
				{
					r++;
				}
				CRect trect(move.x - 20, move.y - 20, move.x + 20, move.y + 20);
				CPoint temp(r, r);
				memdc.RoundRect(trect, temp);
			}
			if (nshape == -1)
			{
				move.fDraw(&memdc);
			}
			dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
			d--;
		}
		cur++;
		scrollbar.SetScrollPos(cur);
		if (cur >= max - 1)
		{
			Sleep(200);
			cur = 0;
			move = list.GetAt(list.GetHeadPosition());
			scrollbar.SetScrollPos(cur);
		}
		right = -1;
		left = -1;
		d = 300.0;
		return;
	}




	memdc.MoveTo(list.GetAt(pos).p);
	while (pos != 0)
	{

		Shape temp = list.GetAt(pos);
		if (b_start == 0)
		{
			temp.fDraw(&memdc);
			memdc.LineTo(temp.p);
		}
		else
		{
			CPen  pen(PS_DASH, 1, RGB(0, 0, 0));
			memdc.SelectObject(&pen);
			memdc.LineTo(temp.p);
		}
		list.GetNext(pos);
	}
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	// Do not call CWnd::OnPaint() for painting messages
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	start.Create(_T(">"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(0, 0, 50, 30), this, 100);
	pause.Create(_T("||"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(50, 0, 100, 30), this, 101);
	save.Create(_T("Save"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(100, 0, 150, 30), this, 102);
	load.Create(_T("Load"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(150, 0, 200, 30), this, 103);
	clear.Create(_T("Clear"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(200, 0, 250, 30), this, 104);
	scrollbar.Create(SBS_HORZ | WS_VISIBLE | WS_CHILD, CRect(250, 0, 600, 30), this, 105);
	// TODO:  Add your specialized creation code here

	return 0;
}
void CChildView::onStart()
{
	pause.SetState(0);
	start.SetState(1);
	POSITION pos = list.GetHeadPosition();
	if (pos != 0)
	{
		cur = 0;
		b_start = 1;
		SetTimer(0, 30, 0);
	}

}
void CChildView::onPause()
{
	KillTimer(0);
	b_start = 0;	
	cur = 0;
	POSITION pos = list.GetHeadPosition();
	if (pos != 0)
	{
		move = list.GetAt(pos);
		list.GetAt(list.GetHeadPosition()).m_clr = RGB(255, 0, 0);
		list.GetAt(list.GetTailPosition()).m_clr = RGB(0, 0, 0);
	}
	start.SetState(0);
	pause.SetState(1);
	scrollbar.SetScrollPos(0);
	CRect rect;
	GetClientRect(rect);
	CRgn rgn;
	CPoint ptv[6];
	ptv[0] = CPoint(600, 0);
	ptv[1] = CPoint(600, 30);
	ptv[2] = CPoint(0, 30);
	ptv[3] = CPoint(0, rect.bottom);
	ptv[4] = CPoint(rect.right, rect.bottom);
	ptv[5] = CPoint(rect.right, 0);
	rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
	InvalidateRgn(&rgn);
}
void CChildView::onSave()
{
	cur = 0;
	CFile f;
	CFileException e;
	if (!f.Open(_T("SaveData.dat"), CFile::modeCreate | CFile::modeReadWrite, &e))
	{
		e.ReportError();
		return;
	}
	CArchive ar(&f, CArchive::store);

	list.Serialize(ar);
	ar.Close();
	f.Close();
}
void CChildView::onLoad()
{
	POSITION pos = list.GetHeadPosition();
	if (pos != 0)
	{
		list.RemoveAll();
	}
	CFile file;
	CFileException e;
	if (!file.Open(_T("SaveData.dat"), CFile::modeReadWrite, &e))
	{
		e.ReportError();
		return;
	}

	CArchive ar(&file, CArchive::load);

	list.Serialize(ar);	
	ar.Close();
	file.Close();
	cur = 0;
	scrollbar.SetScrollPos(0);
	if (list.GetHeadPosition() != 0)
	{
		move = list.GetAt(list.GetHeadPosition());
		list.GetAt(list.GetHeadPosition()).m_clr = RGB(255, 0, 0);
		list.GetAt(list.GetTailPosition()).m_clr = RGB(0, 0, 0);
	}
	CRect rect;
	GetClientRect(rect);
	CRgn rgn;
	CPoint ptv[6];
	ptv[0] = CPoint(600, 0);
	ptv[1] = CPoint(600, 30);
	ptv[2] = CPoint(0, 30);
	ptv[3] = CPoint(0, rect.bottom);
	ptv[4] = CPoint(rect.right, rect.bottom);
	ptv[5] = CPoint(rect.right, 0);
	rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
	InvalidateRgn(&rgn);
	
}
void CChildView::onClean()
{
	KillTimer(0);	
	cur = 0;
	b_start = 0;
	start.SetState(0);
	if (list.GetHeadPosition() != 0)
	{
		list.RemoveAll();
	}
	scrollbar.SetScrollPos(0);
	CRect rect;
	GetClientRect(rect);
	CRgn rgn;
	CPoint ptv[6];
	ptv[0] = CPoint(600, 0);
	ptv[1] = CPoint(600, 30);
	ptv[2] = CPoint(0, 30);
	ptv[3] = CPoint(0, rect.bottom);
	ptv[4] = CPoint(rect.right, rect.bottom);
	ptv[5] = CPoint(rect.right, 0);
	rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
	InvalidateRgn(&rgn);
}
void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int n = list.GetCount();
	pScrollBar->SetScrollRange(0, n - 1);
	int num = pScrollBar->GetScrollPos();
	for (int i = 0; i < n; i++)
	{
		list.GetAt(list.FindIndex(i)).m_clr = RGB(0, 0, 0);
	}
	if (nSBCode == SB_THUMBTRACK)
	{
		pScrollBar->SetScrollPos(nPos);
		POSITION pos = list.FindIndex(nPos);
		if (b_start==0)
		{
			list.GetAt(pos).m_clr = RGB(255, 0, 0);
			CRect rect;
			GetClientRect(rect);
			CRgn rgn;
			CPoint ptv[6];
			ptv[0] = CPoint(600, 0);
			ptv[1] = CPoint(600, 30);
			ptv[2] = CPoint(0, 30);
			ptv[3] = CPoint(0, rect.bottom);
			ptv[4] = CPoint(rect.right, rect.bottom);
			ptv[5] = CPoint(rect.right, 0);
			rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
			InvalidateRgn(&rgn);
		
		}
		if (b_start)
		{
			cur = nPos;
			POSITION tpos=list.FindIndex(cur);
			move = list.GetAt(tpos);
		}
			
	}
	if (nSBCode == SB_LINELEFT)
	{
		POSITION pos = list.FindIndex(num);
		list.GetPrev(pos);
		if (num > 0)
		{
			pScrollBar->SetScrollPos(num - 1);
			if (b_start==0)
			{
				list.GetAt(pos).m_clr = RGB(255, 0, 0);
				CRect rect;
				GetClientRect(rect);
				CRgn rgn;
				CPoint ptv[6];
				ptv[0] = CPoint(600, 0);
				ptv[1] = CPoint(600, 30);
				ptv[2] = CPoint(0, 30);
				ptv[3] = CPoint(0, rect.bottom);
				ptv[4] = CPoint(rect.right, rect.bottom);
				ptv[5] = CPoint(rect.right, 0);
				rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
				InvalidateRgn(&rgn);
			}
			if (b_start)
			{
				cur = num-1;
				if (cur < 0)
				{
					cur = 0;
				}
				move = list.GetAt(pos);
			}
		}
	}
	if (nSBCode == SB_LINERIGHT)
	{
		POSITION pos = list.FindIndex(num);
		int n = list.GetCount()-1;
		list.GetNext(pos);
		if (pos!=0)
		{

			pScrollBar->SetScrollPos(num + 1);
			if (b_start==0)
			{
				list.GetAt(pos).m_clr = RGB(255, 0, 0);
				CRect rect;
				GetClientRect(rect);
				CRgn rgn;
				CPoint ptv[6];
				ptv[0] = CPoint(600, 0);
				ptv[1] = CPoint(600, 30);
				ptv[2] = CPoint(0, 30);
				ptv[3] = CPoint(0, rect.bottom);
				ptv[4] = CPoint(rect.right, rect.bottom);
				ptv[5] = CPoint(rect.right, 0);
				rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
				InvalidateRgn(&rgn);
			}
			if (b_start)
			{
				right = num+1;
				move = list.GetAt(pos);	
				if (num >= n - 1)
				{
					right = n;
					
					move = list.GetAt(list.GetTailPosition());
				}
			}
		}
	}
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (b_start == 0)
	{
		if (list.GetTailPosition() != 0)
		{
			list.GetAt(list.GetHeadPosition()).m_clr = RGB(0, 0, 0);
			list.GetAt(list.GetTailPosition()).m_clr = RGB(0, 0, 0);
		}
		Shape ts;
		ts.mb_shape = 1;
		ts.p = point;
		ts.x = point.x;
		ts.y = point.y;
		ts.m_clr = RGB(255, 0, 0);
		list.AddTail(ts);
		Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (b_start == 0)
	{
		if (list.GetTailPosition() != 0)
		{
			list.GetAt(list.GetHeadPosition()).m_clr = RGB(0, 0, 0);
			list.GetAt(list.GetTailPosition()).m_clr = RGB(0, 0, 0);
		}
		Shape ts;
		ts.mb_shape = 0;
		ts.p = point;
		ts.x = point.x;
		ts.y = point.y;
		ts.m_clr = RGB(255, 0, 0);
		list.AddTail(ts);
		Invalidate();
	}
	// TODO: Add your message handler code here and/or call default

	CWnd::OnRButtonDown(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CWnd::OnEraseBkgnd(pDC);
	return true;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 0)
	{
		if (b_start == 1)
		{
			CRect rect;
			GetClientRect(rect);
			CRgn rgn;
			CPoint ptv[6];
			ptv[0] = CPoint(600, 0);
			ptv[1] = CPoint(600, 30);
			ptv[2] = CPoint(0, 30);
			ptv[3] = CPoint(0, rect.bottom);
			ptv[4] = CPoint(rect.right, rect.bottom);
			ptv[5] = CPoint(rect.right, 0);
			rgn.CreatePolygonRgn(ptv, 6, ALTERNATE);
			InvalidateRgn(&rgn);
		}
	}
	CWnd::OnTimer(nIDEvent);
}
