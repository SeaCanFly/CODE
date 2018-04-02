
// CopyFileCBDlg.h : ��� ����
//

#pragma once

#define WM_COPY_PROGRESS WM_USER + 500

// CCopyFileCBDlg ��ȭ ����
class CCopyFileCBDlg : public CDialogEx
{
	static DWORD CALLBACK CopyProgressRoutine
	(
		LARGE_INTEGER TotalFileSize,
		LARGE_INTEGER TotalBytesTransferred,
		LARGE_INTEGER StreamSize,
		LARGE_INTEGER StreamBytesTransferred,
		DWORD dwStreamNumber,
		DWORD dwCallbackReason,
		HANDLE hSourceFile,
		HANDLE hDestinationFile,
		LPVOID lpData
	);
	static DWORD WINAPI WorkerProc(PVOID);

	CString m_szSrc;
	CString m_szDst;

	HANDLE	m_hWorker;
	DWORD	m_dwState;
	HANDLE	m_hPause;

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
	afx_msg LRESULT OnCopyProgress(WPARAM, LPARAM);
};
