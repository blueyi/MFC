// IGfxTestView.h : interface of the CIGfxTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IGFXTESTVIEW_H__74C4A601_E93C_4005_B6E3_49E7097DCF1A__INCLUDED_)
#define AFX_IGFXTESTVIEW_H__74C4A601_E93C_4005_B6E3_49E7097DCF1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GDIpInterface.h"

using namespace gfxinterface;

class CIGfxTestView : public CView
{
protected: // create from serialization only
	CIGfxTestView();
	DECLARE_DYNCREATE(CIGfxTestView)

// Attributes
public:
	CIGfxTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIGfxTestView)
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
	static void DrawDemo(CGfxInterface* pInterface);
	virtual ~CIGfxTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGDIpInterface* m_pInterface;
	Gdiplus::Bitmap* m_pMemBitmap;
// Generated message map functions
protected:
	//{{AFX_MSG(CIGfxTestView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTestTometafile();
	afx_msg void OnTestMultiouput();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IGfxTestView.cpp
inline CIGfxTestDoc* CIGfxTestView::GetDocument()
   { return (CIGfxTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IGFXTESTVIEW_H__74C4A601_E93C_4005_B6E3_49E7097DCF1A__INCLUDED_)
