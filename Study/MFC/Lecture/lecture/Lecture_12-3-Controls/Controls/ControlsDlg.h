// ControlsDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CControlsDlg ��ȭ ����
class CControlsDlg : public CDialog
{
// ����
public:
	CControlsDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_DIALOGTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_checkButton;
	CButton m_RadioButton1;
	CButton m_RadioButton2;

	void OnStaticClick();
	afx_msg void OnStnClickedStaticImage();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CEdit m_Edit;
	CListBox m_ListBox;
	afx_msg void OnStnClickedStaticImage2();
};
