
// test8.h : main header file for the test8 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest8App:
// See test8.cpp for the implementation of this class
//

class Ctest8App : public CWinApp
{
public:
	Ctest8App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest8App theApp;
