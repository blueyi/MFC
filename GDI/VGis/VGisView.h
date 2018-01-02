// VGisView.h : interface of the CVGisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VGISVIEW_H__3917AD89_3CAA_4DF2_AF69_8241FCAA602D__INCLUDED_)
#define AFX_VGISVIEW_H__3917AD89_3CAA_4DF2_AF69_8241FCAA602D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "GisInterface.h"
#include "VGisDoc.h"
class CVGisView : public CView
{
public:
	CGisInterface m_Gis;
protected: // create from serialization only
	CVGisView();
	DECLARE_DYNCREATE(CVGisView)

// Attributes
public:
	CVGisDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVGisView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void Serialize(CArchive& ar);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVGisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVGisView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawArc();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawLineNet();
	afx_msg void OnDrawMline();
	afx_msg void OnDrawNet();
	afx_msg void OnDrawRgn();
	afx_msg void OnDrawText();
	afx_msg void OnDrawBig();
	afx_msg void OnDrawSmall();
	afx_msg void OnMove();
	afx_msg void OnAll();
	afx_msg void OnRectbig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VGisView.cpp
inline CVGisDoc* CVGisView::GetDocument()
   { return (CVGisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VGISVIEW_H__3917AD89_3CAA_4DF2_AF69_8241FCAA602D__INCLUDED_)
