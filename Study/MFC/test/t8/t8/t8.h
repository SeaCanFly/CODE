
// t8.h : main header file for the t8 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ct8App:
// See t8.cpp for the implementation of this class
//

class Ct8App : public CWinApp
{
public:
	Ct8App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ct8App theApp;
