// ScrollCircle.h : main header file for the ScrollCircle application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScrollCircleApp:
// See ScrollCircle.cpp for the implementation of this class
//

class CScrollCircleApp : public CWinApp
{
public:
	CScrollCircleApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScrollCircleApp theApp;