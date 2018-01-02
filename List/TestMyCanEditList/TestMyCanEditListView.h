// TestMyCanEditListView.h : interface of the CTestMyCanEditListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMYCANEDITLISTVIEW_H__314880A6_368B_4863_892F_2D2125A30FD2__INCLUDED_)
#define AFX_TESTMYCANEDITLISTVIEW_H__314880A6_368B_4863_892F_2D2125A30FD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConditionListCtrl.h"

class CTestMyCanEditListView : public CView
{
protected: // create from serialization only
	CTestMyCanEditListView();
	DECLARE_DYNCREATE(CTestMyCanEditListView)

// Attributes
public:
	CTestMyCanEditListDoc* GetDocument();

// Operations
public:
	CConditionListCtrl m_wndConditionList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMyCanEditListView)
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
	virtual ~CTestMyCanEditListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestMyCanEditListView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestMyCanEditListView.cpp
inline CTestMyCanEditListDoc* CTestMyCanEditListView::GetDocument()
   { return (CTestMyCanEditListDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMYCANEDITLISTVIEW_H__314880A6_368B_4863_892F_2D2125A30FD2__INCLUDED_)
