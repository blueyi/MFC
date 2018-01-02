// XxView.h : interface of the CXxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XXVIEW_H__3B541491_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
#define AFX_XXVIEW_H__3B541491_61A8_11D2_86B6_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CXxView : public CView
{
protected: // create from serialization only
	CXxView();
	DECLARE_DYNCREATE(CXxView)

// Attributes
public:
	CXxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXxView)
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
	virtual ~CXxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXxView)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XxView.cpp
inline CXxDoc* CXxView::GetDocument()
   { return (CXxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XXVIEW_H__3B541491_61A8_11D2_86B6_0040055C08D9__INCLUDED_)
