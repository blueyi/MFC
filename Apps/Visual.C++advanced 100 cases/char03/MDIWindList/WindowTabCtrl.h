#if !defined(AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WindowTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWindowTabCtrl window

class CWindowTabCtrl : public CTabCtrl
{
// Construction
public:
	CWindowTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ResizeTabs();
	virtual ~CWindowTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWindowTabCtrl)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWTABCTRL_H__C67D43AA_F890_11D1_83BA_0000B43382FE__INCLUDED_)
