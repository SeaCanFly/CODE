
#pragma once
#include "BkgrdWorker.h"

// CCopyFileCBDlg ��ȭ ����
class CCopyFileCBDlg : public CDialogEx
{
	static void WINAPI Handler_DoWork(BkgrdWorker*, DoWorkArgs*);
	static void WINAPI Handler_Report(BkgrdWorker*, ProgressChangedArgs*);
	static void WINAPI Handler_Completed(BkgrdWorker*, RunWorkerCompletedArgs*);

	void DoWork(DoWorkArgs*);
	void Report(ProgressChangedArgs*);
	void Completed(RunWorkerCompletedArgs*);

	CString m_szSrc;
	CString m_szDst;

	HANDLE	m_hPause;
	BkgrdWorker m_bw;

// �����Դϴ�.
public:
	CCopyFileCBDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COPYFILECB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnSrc();
	afx_msg void OnBnClickedBtnDst();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPause();
};
