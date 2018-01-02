#if !defined(AFX_DISPLAYVIEW_H__65FC3355_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_DISPLAYVIEW_H__65FC3355_C244_11D6_AFCA_001088A02FAC__INCLUDED_

#include"BigSeeDoc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayView view

class CDisplayView : public CScrollView
{
protected:
	CDisplayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDisplayView)
    enum{NORMAL_IMAGE,ZOOMIN_IMAGE,ZOOMOUT_IMAGE};
// Attributes
public:
	CBigSeeDoc* GetDocument();
	CString m_strDisplayFileName;
    long m_lImagecx;
	long m_lImagecy;
	//LONG cb;
	DWORD m_dwbytes;
	CString m_strDisplayFilePath;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDisplayView();
public:	
	BOOL IsUseRegularScale;
	double m_nScale;
	long m_loriginalYImageSize;
	long m_loriginalXImageSize;
	 BOOL IsHaveImage;
	 UINT m_uiChoice;
	 
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDisplayView)
	afx_msg void OnImageZoomin();
	afx_msg void OnImageZoomout();
	afx_msg void OnScaleAbsolutely();
	afx_msg void OnUpdateScaleAbsolutely(CCmdUI* pCmdUI);
	afx_msg void OnCentySeventyFive();
	afx_msg void OnUpdateCentySeventyFive(CCmdUI* pCmdUI);
	afx_msg void OnCentyFifty();
	afx_msg void OnUpdateCentyFifty(CCmdUI* pCmdUI);
	afx_msg void OnCentyThirty();
	afx_msg void OnUpdateCentyThirty(CCmdUI* pCmdUI);
	afx_msg void OnCentyTwenty();
	afx_msg void OnUpdateCentyTwenty(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImageZoomout(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#ifndef _DEBUG  // debug version in BigSeeView.cpp
inline CBigSeeDoc* CDisplayView::GetDocument()
   { return (CBigSeeDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYVIEW_H__65FC3355_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
