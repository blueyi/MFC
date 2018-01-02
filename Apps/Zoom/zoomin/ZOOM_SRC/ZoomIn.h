// ZoomIn.h : main header file for the QUICKZOOM application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomInApp:
// See ZoomIn.cpp for the implementation of this class
//

class CZoomInApp : public CWinApp
{
	//{{AFX_VIRTUAL(CZoomInApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CZoomInApp)
	//}}AFX_MSG

	afx_msg void OnHelp();
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
