// GradualChangeView.h : interface of the CGradualChangeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRADUALCHANGEVIEW_H__5F8F4B6D_EC7F_4B70_9686_2A2F01EB6E10__INCLUDED_)
#define AFX_GRADUALCHANGEVIEW_H__5F8F4B6D_EC7F_4B70_9686_2A2F01EB6E10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGradualChangeView : public CView
{
protected: // create from serialization only
	CGradualChangeView();
	DECLARE_DYNCREATE(CGradualChangeView)

// Attributes
public:
	CGradualChangeDoc* GetDocument();
	BYTE *m_pb3;
	BYTE *m_pb2;
	BYTE *m_pb1;
	BITMAPINFOHEADER m_header;
	UINT m_nCount;
	UINT m_nCase;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradualChangeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGradualChangeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGradualChangeView)
	afx_msg void OnMyplay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMystop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GradualChangeView.cpp
inline CGradualChangeDoc* CGradualChangeView::GetDocument()
   { return (CGradualChangeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADUALCHANGEVIEW_H__5F8F4B6D_EC7F_4B70_9686_2A2F01EB6E10__INCLUDED_)
