// HistogramDemoView.h : interface of the CHistogramDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTOGRAMDEMOVIEW_H__43EAC3D4_72C1_4DE5_BD8E_AB317F99ED35__INCLUDED_)
#define AFX_HISTOGRAMDEMOVIEW_H__43EAC3D4_72C1_4DE5_BD8E_AB317F99ED35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHistogramDemoView : public CView
{
protected: // create from serialization only
	CHistogramDemoView();
	DECLARE_DYNCREATE(CHistogramDemoView)

// Attributes
public:
	CHistogramDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHistogramDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHistogramDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HistogramDemoView.cpp
inline CHistogramDemoDoc* CHistogramDemoView::GetDocument()
   { return (CHistogramDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMDEMOVIEW_H__43EAC3D4_72C1_4DE5_BD8E_AB317F99ED35__INCLUDED_)
