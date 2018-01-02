#if !defined(AFX_VIEW2_H__8AD5B616_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
#define AFX_VIEW2_H__8AD5B616_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// View2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CView2 form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CView2 : public CFormView
{
public:
	CView2();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CView2)

// Form Data
public:
	//{{AFX_DATA(CView2)
	enum { IDD = IDD_MULTISCREEN_FORM2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CView2)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual ~CView2();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CView2)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW2_H__8AD5B616_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
