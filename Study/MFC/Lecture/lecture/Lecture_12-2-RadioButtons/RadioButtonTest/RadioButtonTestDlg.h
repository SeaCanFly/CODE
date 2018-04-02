// RadioButtonTestDlg.h : 헤더 파일
//

#pragma once


// CRadioButtonTestDlg 대화 상자
class CRadioButtonTestDlg : public CDialog
{
// 생성
public:
	CRadioButtonTestDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_RADIOBUTTONTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	int m_SelectedRadio;

	void OnRadioClick(UINT nID);
public:
	afx_msg void OnBnClickedButton1();
};
