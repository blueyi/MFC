// splittstView.h : interface of the CSplittstView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPLITTSTVIEW_H__FA98B713_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
#define AFX_SPLITTSTVIEW_H__FA98B713_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSplittstView : public CListView
{
protected: // create from serialization only
	CSplittstView();
	DECLARE_DYNCREATE(CSplittstView)

// Attributes
public:
	CSplittstDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplittstView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplittstView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSplittstView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in splittstView.cpp
inline CSplittstDoc* CSplittstView::GetDocument()
   { return (CSplittstDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTSTVIEW_H__FA98B713_D0B7_11D3_BC39_00C04F602FEE__INCLUDED_)
