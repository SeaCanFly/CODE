
// t6.h : main header file for the t6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ct6App:
// See t6.cpp for the implementation of this class
//

class Ct6App : public CWinApp
{
public:
	Ct6App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ct6App theApp;
