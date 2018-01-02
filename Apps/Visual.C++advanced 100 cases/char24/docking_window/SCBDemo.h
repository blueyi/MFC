// SCBDemo.h : main header file for the SCBDEMO application
//

#if !defined(AFX_SCBDEMO_H__50CDA4E5_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
#define AFX_SCBDEMO_H__50CDA4E5_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSCBDemoApp:
// See SCBDemo.cpp for the implementation of this class
//

class CSCBDemoApp : public CWinApp
{
public:
    CSCBDemoApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSCBDemoApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CSCBDemoApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCBDEMO_H__50CDA4E5_EE4A_11D1_AFFC_B4F0A8099228__INCLUDED_)
