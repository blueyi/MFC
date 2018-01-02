// TestPageView.h : interface of the CTestPageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPAGEVIEW_H__A2438D3D_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
#define AFX_TESTPAGEVIEW_H__A2438D3D_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000



class CTestPageView : public CView
{
protected: // create from serialization only
	CTestPageView();
	DECLARE_DYNCREATE(CTestPageView)

// Attributes
public:
	CTestPageDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPageView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestPageView.cpp
inline CTestPageDoc* CTestPageView::GetDocument()
   { return (CTestPageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGEVIEW_H__A2438D3D_1B15_11D2_880E_00C0DFA97DA3__INCLUDED_)
