#if !defined(AFX_MYVIEW2_H__CF47D86F_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
#define AFX_MYVIEW2_H__CF47D86F_5027_11D5_AC0B_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyView2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyView2 form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ZSplitterDlg.h"

class CMyView2 : public ZSplitterDlgImpl<CFormView>
{
protected:
	CMyView2();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyView2)

  // Form Data
public:
	//{{AFX_DATA(CMyView2)
	enum { IDD = IDD_FORMVIEW };
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView2)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyView2();
  virtual void OnDraw(CDC* pDC);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMyView2)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYVIEW_H__CF47D86F_5027_11D5_AC0B_00104B2CD040__INCLUDED_)
