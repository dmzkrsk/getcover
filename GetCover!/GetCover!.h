// GetCover!.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGetCoverApp:
// See GetCover!.cpp for the implementation of this class
//

class CGetCoverApp : public CWinApp
{
public:
	CGetCoverApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGetCoverApp theApp;