// ChildView.h : interface of the CChildView class
//


#pragma once

#include "MyDialog2.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	
	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:							// 추가된것들
	CString m_str;				// 출력 문자
	int m_color;				// 색:	0=빨강, 1=초록, 2=파랑
	CMyDialog2 *m_pDlg;			// 비모달 대화상자 주소
	COLORREF m_userColor;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

