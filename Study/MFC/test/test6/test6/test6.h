
// test6.h : main header file for the test6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest6App:
// See test6.cpp for the implementation of this class
//

class Ctest6App : public CWinApp
{
public:
	Ctest6App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest6App theApp;
