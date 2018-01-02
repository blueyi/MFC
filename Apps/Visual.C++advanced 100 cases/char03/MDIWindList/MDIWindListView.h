// MDIWindListView.h : interface of the CMDIWindListView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDIWINDLISTVIEW_H__C67D439E_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_MDIWINDLISTVIEW_H__C67D439E_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMDIWindListView : public CView
{
protected: // create from serialization only
	CMDIWindListView();
	DECLARE_DYNCREATE(CMDIWindListView)

// Attributes
public:
	CMDIWindListDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIWindListView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDIWindListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMDIWindListView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MDIWindListView.cpp
inline CMDIWindListDoc* CMDIWindListView::GetDocument()
   { return (CMDIWindListDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIWINDLISTVIEW_H__C67D439E_F890_11D1_83BA_0000B43382FE__INCLUDED_)
