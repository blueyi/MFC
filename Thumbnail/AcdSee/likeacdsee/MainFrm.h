// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__65FC3349_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_MAINFRM_H__65FC3349_C244_11D6_AFCA_001088A02FAC__INCLUDED_

#include "BigSeeDoc.h"
#include "DisplayView.h"
#include "LogoToolBar.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	long m_lImagecx;
	long m_lImagecy;
	//CString m_strFilePath; 
	
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBigSeeDoc* m_pCurrentDoc;
	CStatusBar  m_wndStatusBar;
	CLogoToolBar    m_wndToolBar;
    CSplitterWnd m_wndSplitter;


// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnImageOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__65FC3349_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
