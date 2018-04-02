// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication6.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{
	cview = 0;
	a = 0;
	sum = 0;
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MyDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &MyDialog::OnBnClickedButton5)
	ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON6, &MyDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// MyDialog message handlers


void MyDialog::OnBnClickedButton1()
{
	str += "1";
	a = a * 10 + 1;
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton2()
{
	str += "2";
	a = a * 10 + 2;
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton3()
{
	str += "3";
	a = a * 10 + 3;
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton4()
{
	
	/*CString t = str;
	a=_ttoi(t);
	temp.num = a;
	temp.op = "+";
	nl.AddTail(temp);*/
	temp.num = a;
	temp.op = '+';
	nl.AddTail(temp);
	a = 0;
	str += "+";
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton5()
{
	temp.num = a;
	temp.op = '-';
	nl.AddTail(temp);
	a = 0;
	str += "-";
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}


BOOL MyDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO:  Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void MyDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	CDialog::OnOK();
}


void MyDialog::OnBnClickedButton6()
{
	temp.num = a;
	temp.op = ' ';
	nl.AddTail(temp);
	POSITION pos = nl.GetHeadPosition();
	int c = nl.GetAt(pos).num;
	sum = sum + c;
	while (pos != 0)
	{
		POSITION temp = pos;
		nl.GetNext(pos);
		if (nl.GetAt(temp).op == '+')
		{
			sum = sum + nl.GetAt(pos).num;
		}
		if (nl.GetAt(temp).op == '-')
		{
			sum = sum - nl.GetAt(pos).num;
		}

	}
	cview->vsum = sum;
	CString t;
	t.Format(_T("%d"), sum);
	str += "=";
	str += t;
	
	a = 0;
	str = "";
	sum = 0;
	temp.num = 0;
	temp.op = 0;
	nl.RemoveAll();
	cview->vstr = str;
	cview->Invalidate();
	// TODO: Add your control notification handler code here
}
