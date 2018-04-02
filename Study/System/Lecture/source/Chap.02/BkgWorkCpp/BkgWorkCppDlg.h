
// BkgWorkCppDlg.h : ��� ����
//

#pragma once

#include "BkgrdWorker.h"

// CBkgWorkCppDlg ��ȭ ����
class CBkgWorkCppDlg : public CDialogEx
{
	static void WINAPI Handler_DoWork(BkgrdWorker*, DoWorkArgs*);
	static void WINAPI Handler_Report(BkgrdWorker*, ProgressChangedArgs*);
	static void WINAPI Handler_Completed(BkgrdWorker*, RunWorkerCompletedArgs*);

// �����Դϴ�.
public:
	CBkgWorkCppDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CProgressCtrl* GetPrgBar() { return (CProgressCtrl*)GetDlgItem(IDC_PROGRESS); }
	CEdit* GetLogEdit() { return (CEdit*)GetDlgItem(IDC_EDIT_LOG); }

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BKGWORKCPP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	bool m_bClosing;
	HANDLE m_hPause;
	BkgrdWorker m_bw;

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnCancel();
	DECLARE_MESSAGE_MAP()
public:
	DWORD m_dwDelay;
	virtual void OnCancel();
	afx_msg void OnDestroy();
};
