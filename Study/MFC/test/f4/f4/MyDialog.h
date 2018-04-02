#pragma once
#include "afxwin.h"


// MyDialog dialog

class MyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();
	CString dstr;
	COLORREF dclr;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit edit1;
	afx_msg void OnNMThemeChangedScrollbar3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChangedScrollbar2(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	CScrollBar sb1;
	CScrollBar sb2;
	CScrollBar sb3;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
