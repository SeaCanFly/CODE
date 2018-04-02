#pragma once

//#include "ChildView.h"
class CChildView;

// CMyDialog2 ��ȭ �����Դϴ�.

class CMyDialog2 : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog2)

public:
	CMyDialog2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMyDialog2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:				// �߰��� ��

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
