// Timer1.h : Timer1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CTimer1App:
// �� Ŭ������ ������ ���ؼ��� Timer1.cpp�� �����Ͻʽÿ�.
//

class CTimer1App : public CWinApp
{
public:
	CTimer1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTimer1App theApp;