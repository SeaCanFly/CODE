// RadioButtonTestDlg.h : ��� ����
//

#pragma once


// CRadioButtonTestDlg ��ȭ ����
class CRadioButtonTestDlg : public CDialog
{
// ����
public:
	CRadioButtonTestDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_RADIOBUTTONTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
	int m_SelectedRadio;

	void OnRadioClick(UINT nID);
public:
	afx_msg void OnBnClickedButton1();
};
