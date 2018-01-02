// demo_ui_explorerView.h : interface of the CDemo_ui_explorerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_UI_EXPLORERVIEW_H__7BB52B85_0704_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_DEMO_UI_EXPLORERVIEW_H__7BB52B85_0704_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDemo_ui_explorerView : public CEditView
{
protected: // create from serialization only
	CDemo_ui_explorerView();
	DECLARE_DYNCREATE(CDemo_ui_explorerView)

// Attributes
public:
	CDemo_ui_explorerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_ui_explorerView)
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
	virtual ~CDemo_ui_explorerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_ui_explorerView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in demo_ui_explorerView.cpp
inline CDemo_ui_explorerDoc* CDemo_ui_explorerView::GetDocument()
   { return (CDemo_ui_explorerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_UI_EXPLORERVIEW_H__7BB52B85_0704_11D2_AB9F_441100C10000__INCLUDED_)
