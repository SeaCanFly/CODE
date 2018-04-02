
// f4.h : main header file for the f4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cf4App:
// See f4.cpp for the implementation of this class
//

class Cf4App : public CWinApp
{
public:
	Cf4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cf4App theApp;
