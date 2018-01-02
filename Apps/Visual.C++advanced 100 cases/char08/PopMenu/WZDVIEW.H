// WzdView.h : interface of the CWzdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WZDVIEW_H__CA9038F0_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_)
#define AFX_WZDVIEW_H__CA9038F0_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CWzdView : public CView
{
protected: // create from serialization only
	CWzdView();
	DECLARE_DYNCREATE(CWzdView)

// Attributes
public:
	CWzdDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzdView)
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
	virtual ~CWzdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWzdView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPopupWzd1();
	afx_msg void OnPopupWzd2();
	afx_msg void OnPopupWzd3();
	afx_msg void OnPopupWzd4();
	afx_msg void OnPopupWzd5();
	afx_msg void OnPopupWzd6();
	afx_msg void OnPopupWzd7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WzdView.cpp
inline CWzdDoc* CWzdView::GetDocument()
   { return (CWzdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WZDVIEW_H__CA9038F0_B0DF_11D1_A18C_DCB3C85EBD34__INCLUDED_)
