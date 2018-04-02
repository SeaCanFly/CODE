
// 3.h : main header file for the 3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy3App:
// See 3.cpp for the implementation of this class
//

class CMy3App : public CWinApp
{
public:
	CMy3App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy3App theApp;
