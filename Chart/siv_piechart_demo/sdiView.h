// sdiView.h : interface of the CSdiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIVIEW_H__71A686DD_5492_41D1_A65F_C3D37347F1AB__INCLUDED_)
#define AFX_SDIVIEW_H__71A686DD_5492_41D1_A65F_C3D37347F1AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSdiView : public CView
{
protected: // create from serialization only
	CSdiView();
	DECLARE_DYNCREATE(CSdiView)

// Attributes
public:
	CSdiDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdiView)
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
	virtual ~CSdiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSdiView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in sdiView.cpp
inline CSdiDoc* CSdiView::GetDocument()
   { return (CSdiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIVIEW_H__71A686DD_5492_41D1_A65F_C3D37347F1AB__INCLUDED_)
