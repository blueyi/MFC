// GLDouglasView.h : interface of the CGLDouglasView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLDOUGLASVIEW_H__7E30539D_64BE_4A12_BF53_ABF1BD3CCECD__INCLUDED_)
#define AFX_GLDOUGLASVIEW_H__7E30539D_64BE_4A12_BF53_ABF1BD3CCECD__INCLUDED_

#include "viewGL2D.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGLDouglasView : public CView
{
protected: // create from serialization only
	CGLDouglasView();
	DECLARE_DYNCREATE(CGLDouglasView)

// Attributes
public:
	CGLDouglasDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLDouglasView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLDouglasView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CViewGL2D m_view;
	CWGL m_wgl;
	//{{AFX_MSG(CGLDouglasView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GLDouglasView.cpp
inline CGLDouglasDoc* CGLDouglasView::GetDocument()
   { return (CGLDouglasDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLDOUGLASVIEW_H__7E30539D_64BE_4A12_BF53_ABF1BD3CCECD__INCLUDED_)
