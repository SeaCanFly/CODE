#pragma once
#include "afxwin.h"


// MyDialog dialog

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit edit1;
	CString str;
	CString clrstr;
	COLORREF mclr;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit2();
	CEdit edit2;
	CEdit edit3;
	CEdit edit4;
};
