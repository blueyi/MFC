// MultiWindowView.h : interface of the CMultiWindowView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIWINDOWVIEW_H__32913E2D_6D4A_11D0_B063_E8509A000000__INCLUDED_)
#define AFX_MULTIWINDOWVIEW_H__32913E2D_6D4A_11D0_B063_E8509A000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMultiWindowView : public CView
{
protected: // create from serialization only
	CMultiWindowView();
	DECLARE_DYNCREATE(CMultiWindowView)

// Attributes
public:
	CMultiWindowDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiWindowView)
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
	virtual ~CMultiWindowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMultiWindowView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MultiWindowView.cpp
inline CMultiWindowDoc* CMultiWindowView::GetDocument()
   { return (CMultiWindowDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIWINDOWVIEW_H__32913E2D_6D4A_11D0_B063_E8509A000000__INCLUDED_)
