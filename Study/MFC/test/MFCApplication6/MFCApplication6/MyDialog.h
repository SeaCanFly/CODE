#pragma once

#include"ChildView.h"
// MyDialog dialog
#include"MyNum.h"

class MyDialog : public CDialog
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~MyDialog();
	CChildView* cview;
	int a, sum;
	CList<MyNum>nl;
	MyNum temp;
	CList<char>cl;
	CString str;
	CString ostr1;
	CString ostr2;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton6();
};
