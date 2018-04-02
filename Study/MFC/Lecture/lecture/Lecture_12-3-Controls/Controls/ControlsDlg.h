// ControlsDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CControlsDlg 대화 상자
class CControlsDlg : public CDialog
{
// 생성
public:
	CControlsDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_DIALOGTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
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
