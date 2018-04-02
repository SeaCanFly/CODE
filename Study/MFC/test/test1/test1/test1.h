
// test1.h : main header file for the test1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctest1App:
// See test1.cpp for the implementation of this class
//

class Ctest1App : public CWinApp
{
public:
	Ctest1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ctest1App theApp;
