// CListTest.h : CListTest ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCListTestApp:
// �� Ŭ������ ������ ���ؼ��� CListTest.cpp�� �����Ͻʽÿ�.
//

class CCListTestApp : public CWinApp
{
public:
	CCListTestApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCListTestApp theApp;