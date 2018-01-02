// testpgl.h : main header file for the TESTPGL application
//

#if !defined(AFX_TESTPGL_H__02996854_8623_11D4_826B_00A024D26A1F__INCLUDED_)
#define AFX_TESTPGL_H__02996854_8623_11D4_826B_00A024D26A1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
/////////////////////////////////////////////////////////////////////////////
// CTestpglApp:
// See testpgl.cpp for the implementation of this class
//

class CTestpglApp : public CWinApp
{
public:
	CPGLGraph* GenerateGraph();
	CTestpglApp( );

	void SetIdleView (CView* pView) {	m_pIdleView = pView;	m_tStart = clock();};
	void SetAnimatedLine(CPGLGraph* pGraph) 
	{	if (!pGraph) m_pAnimatedLine =NULL; else m_pAnimatedLine = (CPGLLine2D*)pGraph->FindObject(m_uLineID);};
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestpglApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestpglApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void AnimateLine();
	ULONG_PTR m_ulGdiplusToken;
	CView* m_pIdleView;
	CPGLLine2D* m_pAnimatedLine;
	clock_t m_tStart;
	UINT m_uLineID;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPGL_H__02996854_8623_11D4_826B_00A024D26A1F__INCLUDED_)
