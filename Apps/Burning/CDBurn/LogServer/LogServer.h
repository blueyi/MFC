/////////////////////////////////////////////////////////////////////////////
// Project：LOGSERVER
// Author：Paul Dilascia
// Date：星期四, 十一月 07, 2002
// Description：一个简单的系统托盘程序例子，将API函数封装在一个C++类中，实现托盘程序的扩展。
//
/////////////////////////////////////////////////////////////////////////////
// LOGSERVER.h : main header file for the LOGSERVER application
//

#if !defined(AFX_LOGSERVER_H__E52BEFDE_E11D_4205_A949_E21BD891F4CF__INCLUDED_)
#define AFX_LOGSERVER_H__E52BEFDE_E11D_4205_A949_E21BD891F4CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CMyApp:
// See LOGSERVER.cpp for the implementation of this class
//
#ifndef _CHEN_SHI_
#define _CHEN_SHI_
#endif
///////////////////////////////////////////////////////////////////////////////

class CMyApp : public CWinApp
{
public:
	CMyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMyApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CMainFrame* m_pFrame;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGSERVER_H__E52BEFDE_E11D_4205_A949_E21BD891F4CF__INCLUDED_)
