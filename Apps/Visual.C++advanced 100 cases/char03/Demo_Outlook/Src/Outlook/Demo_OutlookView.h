// Demo_OutlookView.h : interface of the CDemo_OutlookView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_Demo_OutlookVIEW_H__7BB52B99_0704_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_Demo_OutlookVIEW_H__7BB52B99_0704_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDemo_OutlookView : public CView
{
protected: // create from serialization only
	CDemo_OutlookView();
	DECLARE_DYNCREATE(CDemo_OutlookView)

// Attributes
public:
	CDemo_OutlookDoc* GetDocument();
	CSplitterWnd m_wndSplitter;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_OutlookView)
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
	virtual ~CDemo_OutlookView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_OutlookView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Demo_OutlookView.cpp
inline CDemo_OutlookDoc* CDemo_OutlookView::GetDocument()
   { return (CDemo_OutlookDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Demo_OutlookVIEW_H__7BB52B99_0704_11D2_AB9F_441100C10000__INCLUDED_)
