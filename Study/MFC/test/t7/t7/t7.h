
// t7.h : main header file for the t7 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ct7App:
// See t7.cpp for the implementation of this class
//

class Ct7App : public CWinApp
{
public:
	Ct7App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ct7App theApp;
