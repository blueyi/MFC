#if !defined(AFX_VIEW3_H__8AD5B617_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
#define AFX_VIEW3_H__8AD5B617_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// View3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CView3 form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CView3 : public CFormView
{
public:
	CView3();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CView3)

// Form Data
public:
	//{{AFX_DATA(CView3)
	enum { IDD = IDD_MULTISCREEN_FORM3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CView3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual ~CView3();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CView3)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW3_H__8AD5B617_7E0A_11D2_BE74_990ECC8F5E7E__INCLUDED_)
