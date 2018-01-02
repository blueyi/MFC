// TextInStatusView.h : interface of the CTextInStatusView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTINSTATUSVIEW_H__9E91315D_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
#define AFX_TEXTINSTATUSVIEW_H__9E91315D_E950_11D4_AFB3_0050BABF4197__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTextInStatusView : public CView
{
protected: // create from serialization only
	CTextInStatusView();
	DECLARE_DYNCREATE(CTextInStatusView)

// Attributes
public:
	CTextInStatusDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextInStatusView)
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
	virtual ~CTextInStatusView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTextInStatusView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextInStatusView.cpp
inline CTextInStatusDoc* CTextInStatusView::GetDocument()
   { return (CTextInStatusDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTINSTATUSVIEW_H__9E91315D_E950_11D4_AFB3_0050BABF4197__INCLUDED_)
