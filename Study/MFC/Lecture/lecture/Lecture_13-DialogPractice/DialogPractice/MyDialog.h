#pragma once


// CMyDialog dialog

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:				// 추가된 것
	
	CString m_str;
	int m_color;
	
	CButton m_colorRadio[3];
	CEdit	m_edit;
	
	BOOL OnInitDialog();
	void OnOK();

	

};
