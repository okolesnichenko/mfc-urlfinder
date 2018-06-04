
// mfcurl.h : main header file for the mfcurl application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CmfcurlApp:
// See mfcurl.cpp for the implementation of this class
//

class CmfcurlApp : public CWinApp
{
public:
	CmfcurlApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateActionSomeaction(CCmdUI *pCmdUI);
};

extern CmfcurlApp theApp;
