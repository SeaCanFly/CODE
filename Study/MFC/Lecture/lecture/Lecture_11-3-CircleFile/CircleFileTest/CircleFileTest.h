// CircleFileTest.h : CircleFileTest ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMyCircleFileTestApp:
// �� Ŭ������ ������ ���ؼ��� CircleFileTest.cpp�� �����Ͻʽÿ�.
//

class CMyCircleFileTestApp : public CWinApp
{
public:
	CMyCircleFileTestApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyCircleFileTestApp theApp;
