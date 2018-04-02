
// t2.h : main header file for the t2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ct2App:
// See t2.cpp for the implementation of this class
//

class Ct2App : public CWinApp
{
public:
	Ct2App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ct2App theApp;
