
// HW4.h : main header file for the HW4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHW4App:
// See HW4.cpp for the implementation of this class
//

class CHW4App : public CWinApp
{
public:
	CHW4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHW4App theApp;
