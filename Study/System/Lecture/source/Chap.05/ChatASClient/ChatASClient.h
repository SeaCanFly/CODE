
// ChatASClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CChatASClientApp:
// �� Ŭ������ ������ ���ؼ��� ChatASClient.cpp�� �����Ͻʽÿ�.
//

class CChatASClientApp : public CWinApp
{
public:
	CChatASClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CChatASClientApp theApp;