
// HW3.h : main header file for the HW3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHW3App:
// See HW3.cpp for the implementation of this class
//

class CHW3App : public CWinApp
{
public:
	CHW3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHW3App theApp;
