// MyDialog2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "DialogPractice.h"
#include "MyDialog2.h"
#include "afxdialogex.h"

#include "ChildView.h"

// CMyDialog2 ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMyDialog2, CDialogEx)

CMyDialog2::CMyDialog2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialog2::IDD, pParent)
{
}

CMyDialog2::~CMyDialog2()
{

}

void CMyDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_STR, m_edit);
	DDX_Text(pDX, IDC_EDIT_STR, m_str);
	DDX_Control(pDX, IDC_RADIO_RED, m_colorRadio[0]);
	DDX_Control(pDX, IDC_RADIO_GREEN, m_colorRadio[1]);
	DDX_Control(pDX, IDC_RADIO_BLUE, m_colorRadio[2]);
}


BEGIN_MESSAGE_MAP(CMyDialog2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CMyDialog2::OnClickedButtonApply)
	ON_BN_CLICKED(IDCANCEL, &CMyDialog2::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CMyDialog2::OnClickedButtonColor)
END_MESSAGE_MAP()


// CMyDialog2 �޽��� ó�����Դϴ�.

BOOL CMyDialog2::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_edit.SetWindowText(m_str);	// DDX_TEXT�� m_str�� �ڵ����� ����Ǿ� �ʿ����. 

	m_colorRadio[m_color].SetCheck(true);

	return true;
}

void CMyDialog2::OnClickedButtonApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);		// DDX�� ���� ���۽�Ų��.
	
	for(int i = 0; i < 3; i++)
		if(m_colorRadio[i].GetCheck())
			m_color = i;

	m_pView->m_str = m_str;
	m_pView->m_color = m_color;
	m_pView->m_userColor = m_userColor;
	m_pView->Invalidate();	// WM_PAINT �޼��� �߻� --> OnPaint() �Լ� ����
}


void CMyDialog2::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DestroyWindow();
//	delete m_pView->m_pDlg;
//	m_pView->m_pDlg = NULL;
//	CDialogEx::OnCancel();
}

void CMyDialog2::OnClickedButtonColor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg(RGB(255, 255, 255), CC_FULLOPEN);
	dlg.DoModal();
	m_userColor = dlg.GetColor(); 
}

void CMyDialog2::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_pView->m_pDlg = NULL;
	delete this;		// ��ȭ���� ��ü�� �ı�

//	CDialogEx::PostNcDestroy();
}



