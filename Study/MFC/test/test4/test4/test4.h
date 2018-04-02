
// test4.h : main header file for the test4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest4App:
// See test4.cpp for the implementation of this class
//

class Ctest4App : public CWinApp
{
public:
	Ctest4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest4App theApp;
