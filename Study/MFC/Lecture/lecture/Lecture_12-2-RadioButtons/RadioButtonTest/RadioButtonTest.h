// RadioButtonTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CRadioButtonTestApp:
// �� Ŭ������ ������ ���ؼ��� RadioButtonTest.cpp�� �����Ͻʽÿ�.
//

class CRadioButtonTestApp : public CWinApp
{
public:
	CRadioButtonTestApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CRadioButtonTestApp theApp;
