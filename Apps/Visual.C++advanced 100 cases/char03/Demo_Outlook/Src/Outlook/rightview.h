#if !defined(AFX_RIGHTVIEW_H__3FF9B7C1_F1C0_11D1_ABA6_442100C10000__INCLUDED_)
#define AFX_RIGHTVIEW_H__3FF9B7C1_F1C0_11D1_ABA6_442100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RightView.h : header file
//
//////////////////////////////////////////////////////////////////////

#include <afxcview.h>

/////////////////////////////////////////////////////////////////////////////
// CRightView view

class CRightView : public CListView
{
protected:
	CRightView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRightView)

	CListCtrl*	m_ListCtrl;
	CHeaderCtrl* m_Header;
	CImageList	m_ImageListNormal;
	CImageList	m_ImageList;
	void BuildColumns();
	void PopulateList(CString* cs = NULL);

// Attributes
public:
	CFont m_Font;

// Operations
public:
	void SetHeaderBitmap(int nCol, int nBitmap, DWORD dwRemove);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRightView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	//{{AFX_MSG(CRightView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnViewList();
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnViewSmall();
	afx_msg void OnUpdateViewSmall(CCmdUI* pCmdUI);
	afx_msg void OnViewLarge();
	afx_msg void OnUpdateViewLarge(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTVIEW_H__3FF9B7C1_F1C0_11D1_ABA6_442100C10000__INCLUDED_)
