// LineDrawing.h : LineDrawing ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CLineDrawingApp:
// �� Ŭ������ ������ ���ؼ��� LineDrawing.cpp�� �����Ͻʽÿ�.
//

class CLineDrawingApp : public CWinApp
{
public:
	CLineDrawingApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLineDrawingApp theApp;