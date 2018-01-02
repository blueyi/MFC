// HDDemoView.h : interface of the CHDDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDDEMOVIEW_H__00C5432F_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
#define AFX_HDDEMOVIEW_H__00C5432F_702E_11D2_ABF7_CCFAF0973072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHDDemoView : public CView
{
protected: // create from serialization only
	CHDDemoView();
	DECLARE_DYNCREATE(CHDDemoView)

// Attributes
public:
	CHDDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDDemoView)
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
	virtual ~CHDDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHDDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HDDemoView.cpp
inline CHDDemoDoc* CHDDemoView::GetDocument()
   { return (CHDDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDDEMOVIEW_H__00C5432F_702E_11D2_ABF7_CCFAF0973072__INCLUDED_)
