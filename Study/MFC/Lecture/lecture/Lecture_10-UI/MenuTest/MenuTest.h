// MenuTest.h : main header file for the MenuTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMenuTestApp:
// See MenuTest.cpp for the implementation of this class
//

class CMenuTestApp : public CWinApp
{
public:
	CMenuTestApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMenuTestApp theApp;