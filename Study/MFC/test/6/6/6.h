
// 6.h : main header file for the 6 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy6App:
// See 6.cpp for the implementation of this class
//

class CMy6App : public CWinApp
{
public:
	CMy6App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy6App theApp;
