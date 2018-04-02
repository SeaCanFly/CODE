// RadioButtonTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RadioButtonTest.h"
#include "RadioButtonTestDlg.h"
#include ".\radiobuttontestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRadioButtonTestDlg ��ȭ ����



CRadioButtonTestDlg::CRadioButtonTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRadioButtonTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRadioButtonTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRadioButtonTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_RADIO1, IDC_RADIO6, OnRadioClick)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CRadioButtonTestDlg �޽��� ó����

BOOL CRadioButtonTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	m_SelectedRadio = 0;

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRadioButtonTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CRadioButtonTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRadioButtonTestDlg::OnRadioClick(UINT nID)
{


	switch(nID)
	{
	case IDC_RADIO1:
		m_SelectedRadio = 1;	break;
	case IDC_RADIO2:
		m_SelectedRadio = 2;	break;
	case IDC_RADIO3:
		m_SelectedRadio = 3;	break;
	case IDC_RADIO4:
		m_SelectedRadio = 4;	break;
	case IDC_RADIO5:
		m_SelectedRadio = 5;	break;
	case IDC_RADIO6:
		m_SelectedRadio = 6;	break;
	default:
		break;
	}

	
}

void CRadioButtonTestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	if (m_SelectedRadio == 0)
		str.Format(_T("���� ��ư�� ���õ��� �ʾ���"));
	else
		str.Format(_T("���õ� ���� ��ư: %d"), m_SelectedRadio);
	AfxMessageBox(str);

}
