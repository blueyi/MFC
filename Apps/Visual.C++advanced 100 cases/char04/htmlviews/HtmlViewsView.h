// HtmlViewsView.h : interface of the CHtmlViewsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTMLVIEWSVIEW_H__DB2D2F5E_1190_11D2_8436_0000B43382FE__INCLUDED_)
#define AFX_HTMLVIEWSVIEW_H__DB2D2F5E_1190_11D2_8436_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ViewH.h"

class CHtmlViewsView : public CHView
{
protected: // create from serialization only
	CHtmlViewsView();
	DECLARE_DYNCREATE(CHtmlViewsView)

// Attributes
public:
	CHtmlViewsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlViewsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHtmlViewsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHtmlViewsView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HtmlViewsView.cpp
inline CHtmlViewsDoc* CHtmlViewsView::GetDocument()
   { return (CHtmlViewsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLVIEWSVIEW_H__DB2D2F5E_1190_11D2_8436_0000B43382FE__INCLUDED_)
