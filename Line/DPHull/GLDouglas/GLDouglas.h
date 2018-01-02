// GLDouglas.h : main header file for the GLDOUGLAS application
//

#if !defined(AFX_GLDOUGLAS_H__4974ABB2_2D96_4850_937C_95EA86AB5951__INCLUDED_)
#define AFX_GLDOUGLAS_H__4974ABB2_2D96_4850_937C_95EA86AB5951__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGLDouglasApp:
// See GLDouglas.cpp for the implementation of this class
//

class CGLDouglasApp : public CWinApp
{
public:
	CGLDouglasApp();

	void SetView(CView* pView)	{	m_pView=pView;};
	CView* GetView()		{	return m_pView;};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLDouglasApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGLDouglasApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CView* m_pView;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLDOUGLAS_H__4974ABB2_2D96_4850_937C_95EA86AB5951__INCLUDED_)
