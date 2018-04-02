// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "f4.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_SCROLLBAR1, sb1);
	DDX_Control(pDX, IDC_SCROLLBAR2, sb2);
	DDX_Control(pDX, IDC_SCROLLBAR3, sb3);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR3, &MyDialog::OnNMThemeChangedScrollbar3)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &MyDialog::OnNMThemeChangedScrollbar1)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR2, &MyDialog::OnNMThemeChangedScrollbar2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// MyDialog message handlers


void MyDialog::OnBnClickedOk()
{
	edit1.GetWindowTextW(dstr);
	int r = sb1.GetScrollPos();
	int g = sb2.GetScrollPos();
	int b = sb3.GetScrollPos();
	dclr = RGB(r, g, b);
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void MyDialog::OnNMThemeChangedScrollbar3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void MyDialog::OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void MyDialog::OnNMThemeChangedScrollbar2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL MyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	sb1.SetScrollRange(0, 255);
	sb2.SetScrollRange(0, 255);
	sb3.SetScrollRange(0, 255);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void MyDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar)
	{
		if (nSBCode == SB_THUMBPOSITION)
		{
			pScrollBar->SetScrollPos(nPos);
		}
		
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
