// DemoToolTipView.h : interface of the CDemoToolTipView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOTOOLTIPVIEW_H__46F58114_3EEB_11D2_8FDB_000000000000__INCLUDED_)
#define AFX_DEMOTOOLTIPVIEW_H__46F58114_3EEB_11D2_8FDB_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ToolTipWnd.h"

class CDemoToolTipView : public CFormView
{
protected: // create from serialization only
	CDemoToolTipView();
	DECLARE_DYNCREATE(CDemoToolTipView)

public:
	//{{AFX_DATA(CDemoToolTipView)
	enum{ IDD = IDD_DEMOTOOLTIP_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CToolTipWnd m_BalloonToolWnd;

// Attributes
public:
	CDemoToolTipDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoToolTipView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoToolTipView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoToolTipView)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoToolTipView.cpp
inline CDemoToolTipDoc* CDemoToolTipView::GetDocument()
   { return (CDemoToolTipDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTOOLTIPVIEW_H__46F58114_3EEB_11D2_8FDB_000000000000__INCLUDED_)
