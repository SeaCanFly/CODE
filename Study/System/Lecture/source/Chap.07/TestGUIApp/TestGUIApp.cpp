
// TestGUIApp.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "TestGUIApp.h"
#include "TestGUIAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGUIAppApp

BEGIN_MESSAGE_MAP(CTestGUIAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestGUIAppApp ����
CTestGUIAppApp::CTestGUIAppApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CTestGUIAppApp ��ü�Դϴ�.

CTestGUIAppApp theApp;


// CTestGUIAppApp �ʱ�ȭ
BOOL CTestGUIAppApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CTestGUIAppDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

