// HeaderCtrlExView.h : interface of the CHeaderCtrlExView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERCTRLEXVIEW_H__1EF0ACAA_95A5_480C_BD7A_198F38F44EFD__INCLUDED_)
#define AFX_HEADERCTRLEXVIEW_H__1EF0ACAA_95A5_480C_BD7A_198F38F44EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HeaderCtrlExt.h"
class CHeaderCtrlExView : public CListView
{
protected: // create from serialization only
	CHeaderCtrlExView();
	DECLARE_DYNCREATE(CHeaderCtrlExView)

// Attributes
public:
	CHeaderCtrlExDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlExView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CHeaderCtrlExView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlExView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CFont m_NewHeaderFont;
	CHeaderCtrlEx m_HeaderCtrl;
};

#ifndef _DEBUG  // debug version in HeaderCtrlExView.cpp
inline CHeaderCtrlExDoc* CHeaderCtrlExView::GetDocument()
   { return (CHeaderCtrlExDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEADERCTRLEXVIEW_H__1EF0ACAA_95A5_480C_BD7A_198F38F44EFD__INCLUDED_)
