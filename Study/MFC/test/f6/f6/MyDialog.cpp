// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "f6.h"
#include "MyDialog.h"
#include "afxdialogex.h"


// MyDialog dialog

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	cv = 0;
	a = 0;
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MyDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MyDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &MyDialog::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &MyDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// MyDialog message handlers


void MyDialog::OnBnClickedButton1()
{
	a = a * 10 + 1;
	str += "1";
	cv->vstr = str;
	cv->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	a = a * 10 + 2;
	str += "2";
	cv->vstr = str;
	cv->Invalidate();
}


void MyDialog::OnBnClickedButton3()
{
	a = a * 10 + 3;
	str += "3";
	cv->vstr = str;
	cv->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton4()
{
	str += "+";
	n.num = a;
	n.p = '+';
	op.AddTail(n);
	a = 0;
	cv->vstr = str;
	cv->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton5()
{
	str += "-";
	n.num = a;
	n.p = '-';
	op.AddTail(n);
	a = 0;
	cv->vstr = str;
	cv->Invalidate();
	// TODO: Add your control notification handler code here
}


void MyDialog::OnBnClickedButton6()
{
	n.num = a;
	n.p = '=';
	op.AddTail(n);
	a = 0;
	str += "=";
	POSITION pos = op.GetHeadPosition();
	int sum = op.GetAt(pos).num;
	while (pos)
	{
		POSITION ppos = pos;
		op.GetNext(pos);
		if (op.GetAt(ppos).p == '+')
		{
			sum += op.GetAt(pos).num;
		}
		if (op.GetAt(ppos).p == '-')
		{
			sum -= op.GetAt(pos).num;
		}
	}
	CString t;
	t.Format(_T("%d"), sum);
	str += t;
	cv->vstr = str;
	str = "";
	op.RemoveAll();
	cv->Invalidate();
	// TODO: Add your control notification handler code here
}
