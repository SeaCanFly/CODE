
// TestGUIApp.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestGUIAppApp:
// �� Ŭ������ ������ ���ؼ��� TestGUIApp.cpp�� �����Ͻʽÿ�.
//

class CTestGUIAppApp : public CWinApp
{
public:
	CTestGUIAppApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestGUIAppApp theApp;