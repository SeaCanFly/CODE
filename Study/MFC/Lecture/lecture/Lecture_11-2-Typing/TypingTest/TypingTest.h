// TypingTest.h : TypingTest ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"       // �� ��ȣ


// CTypingTestApp:
// �� Ŭ������ ������ ���ؼ��� TypingTest.cpp�� �����Ͻʽÿ�.
//

class CTypingTestApp : public CWinApp
{
public:
	CTypingTestApp();


// ������
public:
	virtual BOOL InitInstance();

// ����

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTypingTestApp theApp;
