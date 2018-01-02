// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1402A010_DBB1_47A7_9604_7375A55B2EBE__INCLUDED_)
#define AFX_MAINFRM_H__1402A010_DBB1_47A7_9604_7375A55B2EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ToolBarPlayer.h"

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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void DockControlBarLeftOf(CToolBar *Bar, CToolBar *LeftOf);

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;
	CToolBarShrink m_wndToolBarShrink;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAnimationStart();
	afx_msg void OnAnimationStop();
	afx_msg void OnUpdateAnimationStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAnimationStop(CCmdUI* pCmdUI);
	afx_msg void OnDatasampleLoadsample();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1402A010_DBB1_47A7_9604_7375A55B2EBE__INCLUDED_)
