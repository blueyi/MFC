// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_)
#define AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_

#include "DirectoryTreeBar.h"
#include "PreviewBar.h"

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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDirectoryTreeBar m_wndDirTreeBar;
	CPreviewBar	m_wndPreviewBar;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BOOL m_bShowPreviewBar, m_bShowDirectoryBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewDirectoryBar();
	afx_msg void OnUpdateViewDirectoryBar(CCmdUI* pCmdUI);
	afx_msg void OnViewPreviewBar();
	afx_msg void OnUpdateViewPreviewBar(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnStopThread();
	afx_msg void OnUpdateStopThread(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F46372F6_ED98_4BD5_8334_0F6DB1F3F910__INCLUDED_)
