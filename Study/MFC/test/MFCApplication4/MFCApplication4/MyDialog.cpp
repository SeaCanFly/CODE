// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication4.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_EDIT2, edit2);
	DDX_Control(pDX, IDC_EDIT3, edit3);
	DDX_Control(pDX, IDC_EDIT4, edit4);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &MyDialog::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &MyDialog::OnEnChangeEdit2)
END_MESSAGE_MAP()


// MyDialog message handlers


void MyDialog::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void MyDialog::OnBnClickedOk()
{
	edit1.GetWindowTextW(str);
	edit2.GetWindowTextW(clrstr);
	int r = _ttoi(clrstr);
	clrstr = "";
	edit3.GetWindowTextW(clrstr);
	int g = _ttoi(clrstr);
	clrstr = "";
	edit4.GetWindowTextW(clrstr);
	int b = _ttoi(clrstr);
	clrstr = "";
	mclr = RGB(r, g, b);
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}


void MyDialog::OnEnChangeEdit2()
{
	
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
