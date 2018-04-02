
// test7.h : main header file for the test7 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest7App:
// See test7.cpp for the implementation of this class
//

class Ctest7App : public CWinApp
{
public:
	Ctest7App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest7App theApp;
