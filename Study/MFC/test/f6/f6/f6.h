
// f6.h : main header file for the f6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cf6App:
// See f6.cpp for the implementation of this class
//

class Cf6App : public CWinApp
{
public:
	Cf6App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cf6App theApp;
