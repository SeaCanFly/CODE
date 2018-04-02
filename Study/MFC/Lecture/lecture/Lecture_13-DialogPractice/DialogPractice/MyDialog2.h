#pragma once

//#include "ChildView.h"
class CChildView;

// CMyDialog2 대화 상자입니다.

class CMyDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog2)

public:
	CMyDialog2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMyDialog2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:				// 추가된 것

	CString m_str;
	int m_color;
	CChildView *m_pView;

	CButton m_colorRadio[3];
	CEdit	m_edit;
	COLORREF m_userColor;

	BOOL OnInitDialog();

	afx_msg void OnClickedButtonApply();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickedButtonColor();

	virtual void PostNcDestroy();
};
