
// HW2_WangYiSen.h : main header file for the HW2_WangYiSen application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHW2_WangYiSenApp:
// See HW2_WangYiSen.cpp for the implementation of this class
//

class CHW2_WangYiSenApp : public CWinApp
{
public:
	CHW2_WangYiSenApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHW2_WangYiSenApp theApp;
