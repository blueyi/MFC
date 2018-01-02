// FileEditDemo.h : main header file for the FILEEDITDEMO application
//

#if !defined(AFX_FILEEDITDEMO_H__C9C86F84_5803_11D5_B625_A6E8A2E11D22__INCLUDED_)
#define AFX_FILEEDITDEMO_H__C9C86F84_5803_11D5_B625_A6E8A2E11D22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileEditDemoApp:
// See FileEditDemo.cpp for the implementation of this class
//

class CFileEditDemoApp : public CWinApp
{
public:
    CFileEditDemoApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CFileEditDemoApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CFileEditDemoApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEDITDEMO_H__C9C86F84_5803_11D5_B625_A6E8A2E11D22__INCLUDED_)
