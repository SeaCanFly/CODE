
// TestGUIAppDlg.h : ��� ����
//

#pragma once


// CTestGUIAppDlg ��ȭ ����
class CTestGUIAppDlg : public CDialogEx
{
	HANDLE m_hEvent;

// �����Դϴ�.
public:
	CTestGUIAppDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CTestGUIAppDlg(HANDLE hEvent, CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TESTGUIAPP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
