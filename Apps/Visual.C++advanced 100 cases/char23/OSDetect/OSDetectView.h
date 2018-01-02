// OSDetectView.h : interface of the COSDetectView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OSDETECTVIEW_H__EBEB957E_3821_11D2_8B51_000000000000__INCLUDED_)
#define AFX_OSDETECTVIEW_H__EBEB957E_3821_11D2_8B51_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COSDetectView : public CView
{
protected: // create from serialization only
	COSDetectView();
	DECLARE_DYNCREATE(COSDetectView)

// Attributes
public:
	COSDetectDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COSDetectView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COSDetectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COSDetectView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OSDetectView.cpp
inline COSDetectDoc* COSDetectView::GetDocument()
   { return (COSDetectDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OSDETECTVIEW_H__EBEB957E_3821_11D2_8B51_000000000000__INCLUDED_)
