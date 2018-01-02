#if !defined(AFX_WZDTOOLBAR_H__0939E911_E0EC_11D1_9B7A_00AA003D8695__INCLUDED_)
#define AFX_WZDTOOLBAR_H__0939E911_E0EC_11D1_9B7A_00AA003D8695__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WzdTlBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWzdToolBar window

class CWzdToolBar : public CToolBar
{
// Construction
public:
	CWzdToolBar();

// Attributes
public:

// Operations
public:
	BOOL LoadToolBarEx(UINT id);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzdToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWzdToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWzdToolBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WZDTOOLBAR_H__0939E911_E0EC_11D1_9B7A_00AA003D8695__INCLUDED_)
