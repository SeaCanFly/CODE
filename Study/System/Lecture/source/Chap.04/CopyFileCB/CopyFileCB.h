
// CopyFileCB.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCopyFileCBApp:
// �� Ŭ������ ������ ���ؼ��� CopyFileCB.cpp�� �����Ͻʽÿ�.
//

class CCopyFileCBApp : public CWinApp
{
public:
	CCopyFileCBApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCopyFileCBApp theApp;