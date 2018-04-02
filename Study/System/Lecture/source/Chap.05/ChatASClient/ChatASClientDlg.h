#pragma once
#include "Winsock2.h"
#pragma comment(lib, "Ws2_32.lib")

#define WM_SOCK_NOTI	WM_USER + 100

// CChatASClientDlg ��ȭ ����
class CChatASClientDlg : public CDialogEx
{
	SOCKET m_hSock;

	void UpdateChatView(PCTSTR);

// �����Դϴ�.
public:
	CChatASClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CHATASCLIENT_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnSockNoti(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
