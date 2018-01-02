// Demo_DevStudioView.h : interface of the CDemo_DevStudioView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMO_DEVSTUDIOVIEW_H__90DA7531_7056_11D2_ABA3_640300C10000__INCLUDED_)
#define AFX_DEMO_DEVSTUDIOVIEW_H__90DA7531_7056_11D2_ABA3_640300C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDemo_DevStudioView : public CHtmlView
{
protected: // create from serialization only
	CDemo_DevStudioView();
	DECLARE_DYNCREATE(CDemo_DevStudioView)

// Attributes
public:
	CDemo_DevStudioDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_DevStudioView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemo_DevStudioView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemo_DevStudioView)
	afx_msg void OnWebback();
	afx_msg void OnWebforward();
	afx_msg void OnWebhome();
	afx_msg void OnWebrefresh();
	afx_msg void OnWebstop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Demo_DevStudioView.cpp
inline CDemo_DevStudioDoc* CDemo_DevStudioView::GetDocument()
   { return (CDemo_DevStudioDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_DEVSTUDIOVIEW_H__90DA7531_7056_11D2_ABA3_640300C10000__INCLUDED_)
