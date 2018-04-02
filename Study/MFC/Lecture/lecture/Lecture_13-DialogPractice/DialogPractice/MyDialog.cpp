// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DialogPractice.h"
#include "MyDialog.h"


// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialog)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
	, m_str(_T(""))
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_STR, m_edit);
	DDX_Text(pDX, IDC_EDIT_STR, m_str);
	DDX_Control(pDX, IDC_RADIO_RED, m_colorRadio[0]);
	DDX_Control(pDX, IDC_RADIO_GREEN, m_colorRadio[1]);
	DDX_Control(pDX, IDC_RADIO_BLUE, m_colorRadio[2]);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
END_MESSAGE_MAP()


// CMyDialog message handlers

BOOL CMyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//m_edit.SetWindowText(m_str);	// DDX_TEXT로 m_str과 자동으로 연결되어 필요없음. 

	m_colorRadio[m_color].SetCheck(true);

	return true;
}

void CMyDialog::OnOK()
{
	//m_edit.GetWindowText(m_str);	// DDX_TEXT로 m_str과 자동으로 연결되어 필요없음. 

	for(int i=0; i<3; i++)
		if(m_colorRadio[i].GetCheck())
			m_color = i;
		
	CDialog::OnOK();
}