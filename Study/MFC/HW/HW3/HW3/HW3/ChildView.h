
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Line.h"
#include "MyPoint.h"
#include "MyEraser.h"
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	Line line;
	MyPoint pt;
	MyEraser eraser;
	CPoint startp;
	int mx, my;
	bool key;
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
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnColorBlack();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI *pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMoveeraser();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateMoveeraser(CCmdUI *pCmdUI);
};

