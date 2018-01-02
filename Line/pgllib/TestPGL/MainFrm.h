// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__02996858_8623_11D4_826B_00A024D26A1F__INCLUDED_)
#define AFX_MAINFRM_H__02996858_8623_11D4_826B_00A024D26A1F__INCLUDED_

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
	//}}AFX_VIRTUAL

// Implementation
public:
	void GetExample4(CPGLRegion* pGraph);
	void GetExample3(CPGLRegion* pGraph);
	void GetExample2(CPGLRegion* pGraph);
	void GetExample1(CPGLRegion* pGraph);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGraphGenerategraph();
	afx_msg void OnGraphShow();
	afx_msg void OnTestChangemenu();
	afx_msg void OnTestStartanimation();
	afx_msg void OnTestStopanimation();
	afx_msg void OnExamplesSimpleline();
	afx_msg void OnExamplesSimplelinewithlevelofdetail();
	afx_msg void OnExamplesCustomizingtheaxis();
	afx_msg void OnExamplesSubplotting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__02996858_8623_11D4_826B_00A024D26A1F__INCLUDED_)
