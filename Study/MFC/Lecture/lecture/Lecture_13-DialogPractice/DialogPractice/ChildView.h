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

public:							// �߰��Ȱ͵�
	CString m_str;				// ��� ����
	int m_color;				// ��:	0=����, 1=�ʷ�, 2=�Ķ�
	CMyDialog2 *m_pDlg;			// ���� ��ȭ���� �ּ�
	COLORREF m_userColor;

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

