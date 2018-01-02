#if !defined(AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_)
#define AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_

#include "HeaderCtrlEx1.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlExtention.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlExtention window

class CListCtrlExtention : public CListCtrl
{
// Construction
public:
	CListCtrlExtention();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlExtention)
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CListCtrlExtention();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlExtention)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEXTENTION_H__CA4A6739_6A8B_4AC1_A683_E3389A52C3F1__INCLUDED_)
