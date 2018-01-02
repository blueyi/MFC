// MainFrm.h : interface of the CMainFrame class
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__7BB52B81_0704_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_MAINFRM_H__7BB52B81_0704_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

////////////////
// Special CAnimateCtrl initializes control
//

class CAnimate : public CAnimateCtrl
{
protected:
	DECLARE_DYNAMIC(CAnimate)

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimate)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimate)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////
// Special combo box handles drop down event
//

class CCombo : public CComboBox
{
protected:
	DECLARE_DYNAMIC(CCombo)
	CFont m_font;

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCombo)
	//}}AFX_VIRTUAL

// Generated message map functions
protected:
	//{{AFX_MSG(CCombo)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropDown();
	afx_msg void OnSelendok();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////
// CRebar: creates bands.
//
class CRebar : public CCoolBar
{
protected:
	CToolBar		m_wndToolBar;	// toolbar
	CToolBar 		m_wndIE4tBar;	// toolbar
	CCombo  		m_wndCombo;		// combo box
	CAnimate        m_wndAvi;		// animation control
	HBITMAP		    m_hBmp;
	CImageList		m_list1;
	CImageList		m_list2;
	CImageList		m_list3;
	CImageList		m_list4;
	CRebarBandInfo  m_rbbi;
	
public:
	virtual BOOL    OnCreateBands();
	BOOL CreateToolbarBand();
	BOOL CreateIE4TbarBand();
	BOOL CreateComboBxBand();
	BOOL CreateAviCtrlBand();
};

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

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CRebar      m_wndRebar;
	CMenuMgr	m_menuManager;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__7BB52B81_0704_11D2_AB9F_441100C10000__INCLUDED_)
