// DialogPractice.h : main header file for the DialogPractice application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDialogPracticeApp:
// See DialogPractice.cpp for the implementation of this class
//

class CDialogPracticeApp : public CWinApp
{
public:
	CDialogPracticeApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDialogPracticeApp theApp;