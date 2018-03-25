
// ChildView.h : interface of the CChildView class
//


#pragma once
#include"Shape.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	CList<Shape>list;
	CButton start;
	bool b_start;
	CButton pause;
	CButton save;
	CButton load;
	CButton clear;
	CScrollBar scrollbar;
	Shape move;
	int r,cur,left,right;
	double mx, my,d;
	int nshape;
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
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	 void onStart();
	afx_msg void onPause();
	 void onClean();
	 void onSave();
	 void onLoad();
};

