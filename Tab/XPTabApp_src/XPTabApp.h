/////////////////////////////////////////////////////////////////////////////
// XPTabApp.h : main header file for the XPTabApp application
// See XPTabApp.cpp for the implementation of this class
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPTABAPP_H__B39AA2CA_684D_11D8_97C8_0002A522F13C__INCLUDED_)
#define AFX_XPTABAPP_H__B39AA2CA_684D_11D8_97C8_0002A522F13C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXPTabApp:
class CXPTabApp : public CWinApp
{
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPTabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXPTabApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_XPTABAPP_H__B39AA2CA_684D_11D8_97C8_0002A522F13C__INCLUDED_)
