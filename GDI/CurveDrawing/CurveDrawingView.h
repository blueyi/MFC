// CurveDrawingView.h : interface of the CCurveDrawingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEDRAWINGVIEW_H__DB76B079_5DEB_4483_A8E7_C87447F5B756__INCLUDED_)
#define AFX_CURVEDRAWINGVIEW_H__DB76B079_5DEB_4483_A8E7_C87447F5B756__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "windows.h"
#include "UpPaneView.h"
#include "MyView.h"
#include "EditPaneView.h"
#include "MainFrm.h"
class CCurveDrawingView : public CView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CCurveDrawingView)
   
// Attributes
public:

	CCurveDrawingView();
	CCurveDrawingDoc* GetDocument();
// Operations
public:
//	CSplitterWnd m_wndSplitter;
//	CUpPaneView m_uppaneview;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveDrawingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCurveDrawingView();
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCurveDrawingView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRun();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CurveDrawingView.cpp
inline CCurveDrawingDoc* CCurveDrawingView::GetDocument()
   { return (CCurveDrawingDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDRAWINGVIEW_H__DB76B079_5DEB_4483_A8E7_C87447F5B756__INCLUDED_)
