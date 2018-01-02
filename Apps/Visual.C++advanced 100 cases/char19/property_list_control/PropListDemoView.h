// PropListDemoView.h : interface of the CPropListDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPLISTDEMOVIEW_H__5B23486F_2251_11D2_94BD_00207811FA68__INCLUDED_)
#define AFX_PROPLISTDEMOVIEW_H__5B23486F_2251_11D2_94BD_00207811FA68__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FPSPropertyList.h"

class CPropListDemoView : public CView
{
protected: // create from serialization only
	CPropListDemoView();
	DECLARE_DYNCREATE(CPropListDemoView)

// Attributes
public:
	CFPSPropertyList	m_nPropList;
	CPropListDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropListDemoView)
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
	virtual ~CPropListDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPropListDemoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddItemsToPropList();
};

#ifndef _DEBUG  // debug version in PropListDemoView.cpp
inline CPropListDemoDoc* CPropListDemoView::GetDocument()
   { return (CPropListDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPLISTDEMOVIEW_H__5B23486F_2251_11D2_94BD_00207811FA68__INCLUDED_)
