
// 4.h : main header file for the 4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy4App:
// See 4.cpp for the implementation of this class
//

class CMy4App : public CWinApp
{
public:
	CMy4App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy4App theApp;
