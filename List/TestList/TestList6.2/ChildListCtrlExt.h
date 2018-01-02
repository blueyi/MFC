#if !defined(AFX_CHILDLISTCTRLEXT_H__1B1D5795_7C57_11E0_9049_0050BF29759A__INCLUDED_)
#define AFX_CHILDLISTCTRLEXT_H__1B1D5795_7C57_11E0_9049_0050BF29759A__INCLUDED_

#include "ListCtrlExt.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildListCtrlExt.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildListCtrlExt window

class CChildListCtrlExt : public CListCtrlExt
{
// Construction
public:
	CChildListCtrlExt();

// Attributes
public:
	friend class CTestList6View;

// Operations
public:

#ifdef _DEBUG
	virtual void AssertValid() const {};
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildListCtrlExt)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildListCtrlExt();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildListCtrlExt)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDLISTCTRLEXT_H__1B1D5795_7C57_11E0_9049_0050BF29759A__INCLUDED_)
