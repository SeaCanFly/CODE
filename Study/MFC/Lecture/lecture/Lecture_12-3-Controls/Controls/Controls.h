// Controls.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CControlsApp:
// �� Ŭ������ ������ ���ؼ��� Controls.cpp�� �����Ͻʽÿ�.
//

class CControlsApp : public CWinApp
{
public:
	CControlsApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CControlsApp theApp;
