// DemoTBarCView.h : interface of the CDemoTBarCView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOTBARCVIEW_H__1C587870_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_)
#define AFX_DEMOTBARCVIEW_H__1C587870_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemoTBarCView : public CView
{
protected: // create from serialization only
	CDemoTBarCView();
	DECLARE_DYNCREATE(CDemoTBarCView)

// Attributes
public:
	CDemoTBarCDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoTBarCView)
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
	virtual ~CDemoTBarCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoTBarCView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoTBarCView.cpp
inline CDemoTBarCDoc* CDemoTBarCView::GetDocument()
   { return (CDemoTBarCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTBARCVIEW_H__1C587870_9927_11D2_ABA4_B4FFFFC00000__INCLUDED_)
