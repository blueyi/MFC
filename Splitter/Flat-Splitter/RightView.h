// RightView.h : interface of the CFlatSplitter_DemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RIGHTVIEW_H__F8FC091E_3183_4895_93A6_76049DB8321C__INCLUDED_)
#define AFX_RIGHTVIEW_H__F8FC091E_3183_4895_93A6_76049DB8321C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRightView : public CView
{
protected: // create from serialization only
	CRightView();
	DECLARE_DYNCREATE(CRightView)

// Attributes
public:
	CEdit m_wndEdit;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRightView();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRightView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATSPLITTER_DEMOVIEW_H__F8FC091E_3183_4895_93A6_76049DB8321C__INCLUDED_)
