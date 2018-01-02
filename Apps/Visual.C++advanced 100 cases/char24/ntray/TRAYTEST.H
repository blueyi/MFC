#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

class CTrayApp : public CWinApp
{
public:
	CTrayApp();

protected:
	//{{AFX_VIRTUAL(CTrayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrayApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  BOOL bDisplayingAboutBox;
};

