// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

/*##################################################################

  Author:	Masoud Samimi
  Website:	www.geocities.com/samimi73
  Email:	marcello43@hotmail.com

  Program:	Spinners Toolbar
  History:	05.01.1999 (dd.mm.yy)
  
  Purpose: Please visit my website, it is expalined there.
  

Important Notice:

	This Method and the Application is Copyright(c) Masoud Samimi 1999,2000.
	You can freely use it as long as you credit me for it.

	No guarantee/warantee, expressed or implied is given on this app and I will not be responsible 
	for any damage to you, your property or any other person from using it.
	USE IT ON YOUR OWN RISK.

	Thankyou and have FUNNE =-)

	Masoud Samimi.

##################################################################*/

#if !defined(AFX_MAINFRM_H__D8FEDCE9_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
#define AFX_MAINFRM_H__D8FEDCE9_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpinnerToolBar.h"
#include "SlideToolBar.h"
#include "SpinnerTBView.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

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
	CToolBar    m_wndToolBar;
		
public:
	
	//##########################################//
	// Declare and create function

	CSpinToolBar m_wndSpinBar;
	BOOL CreateSpinnerBar();

	CSlideToolBar m_wndSlideBar;
	BOOL CreateSlideBar();

	CSpinnerTBView* m_pActiveView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSpinnerbar();
	afx_msg void OnUpdateSpinnerbar(CCmdUI* pCmdUI);
	afx_msg void OnViewSliderbar();
	afx_msg void OnUpdateViewSliderbar(CCmdUI* pCmdUI);
	//}}AFX_MSG

	// User defined messages for pane text update
	afx_msg LRESULT OnUpdateTextColor(WPARAM wParam, LPARAM lParam);
	
	// User defined messages for spinners update
	afx_msg LRESULT OnUpdateSpinnerColorRed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateSpinnerColorGreen(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateSpinnerColorBlue(WPARAM wParam, LPARAM lParam);

	// User defined message for slider fill update
	afx_msg LRESULT OnUpdateGradientFill(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdateGradientPane(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D8FEDCE9_5D82_11D4_BEC3_FE8979D1AC45__INCLUDED_)
