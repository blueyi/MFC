#if !defined(AFX_WZD2VIEW_H__BA398476_BE65_11D1_9B54_00AA003D8695__INCLUDED_)
#define AFX_WZD2VIEW_H__BA398476_BE65_11D1_9B54_00AA003D8695__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Wzd2View.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWzd2View view

class CWzd2View : public CView
{
protected:
	CWzd2View();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWzd2View)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWzd2View)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWzd2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWzd2View)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WZD2VIEW_H__BA398476_BE65_11D1_9B54_00AA003D8695__INCLUDED_)
