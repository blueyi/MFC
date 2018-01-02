// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__8AD5B60A_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
#define AFX_MAINFRM_H__8AD5B60A_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

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
	void SwitchToForm(int nForm);
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
	afx_msg void OnForm1();
	afx_msg void OnForm2();
	afx_msg void OnForm3();
	afx_msg void OnForm4();
	afx_msg void OnUpdateForm1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForm2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForm3(CCmdUI* pCmdUI);
	afx_msg void OnUpdateForm4(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__8AD5B60A_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
