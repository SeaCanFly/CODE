// CFileTest.h : CFileTest ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMyCFileTestApp:
// �� Ŭ������ ������ ���ؼ��� CFileTest.cpp�� �����Ͻʽÿ�.
//

class CMyCFileTestApp : public CWinApp
{
public:
	CMyCFileTestApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyCFileTestApp theApp;