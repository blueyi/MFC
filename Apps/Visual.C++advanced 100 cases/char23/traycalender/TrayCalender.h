// TrayCalender.h : main header file for the TRAYCALENDER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "SystemTray.h"


#define	WM_ICON_NOTIFY			WM_USER+10

/////////////////////////////////////////////////////////////////////////////
// CTrayCalenderApp:
// See TrayCalender.cpp for the implementation of this class
//

class CTrayCalenderApp : public CWinApp
{
// Operations
public:
	CTrayCalenderApp();
	HICON CheckDate();

// Attributes
public:
	CString m_strWindowName;		// Window name for application
	HICON   m_hIcon;				// icon for todays date

	BOOL m_bAutoShuffle;
	UINT m_nShuffleDelay;
	BOOL m_bCheckDate;

// Attributes
protected:
	CTime m_StartTime;			// Time that the application started.
	int   m_CurrentDay;			// Current day of month
	BOOL  m_bShuffled;

	BOOL m_bPrevInstance;
	BOOL FirstInstance();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayCalenderApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	void GetApplicationSettings();
	void SaveApplicationSettings();

	//{{AFX_MSG(CTrayCalenderApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTrayCalenderApp theApp;


/////////////////////////////////////////////////////////////////////////////
