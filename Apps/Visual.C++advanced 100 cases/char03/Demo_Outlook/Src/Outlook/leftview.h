#if !defined(AFX_LEFTVIEW_H__3FF9B7C2_F1C0_11D1_ABA6_442100C10000__INCLUDED_)
#define AFX_LEFTVIEW_H__3FF9B7C2_F1C0_11D1_ABA6_442100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LeftView.h : header file
//
//////////////////////////////////////////////////////////////////////

#include <Afxcview.h>

/////////////////////////////////////////////////////////////////////////////
// CLeftView view

class CLeftView : public CTreeView
{
protected:
	CLeftView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftView)

	CFont m_Font;
	CTreeCtrl*	m_TreeCtrl;
	CImageList	m_ImageList;
	void AddTreeChildren( HTREEITEM htiParent );

public:
	HTREEITEM m_htParent;
	CString m_cs[2];
	virtual HTREEITEM GetLastItem( HTREEITEM hItem );
	virtual HTREEITEM GetNextItem( HTREEITEM hItem );
	virtual HTREEITEM GetPrevItem( HTREEITEM hItem );
	virtual HTREEITEM FindItem(CString &sSearch, 
				BOOL bCaseSensitive = FALSE, 
				BOOL bDownDir = TRUE, 
				BOOL bWholeWord = FALSE, 
				HTREEITEM hItem = NULL);
protected:
	virtual BOOL IsFindValid( HTREEITEM );

// Attributes
public:

// Operations
public:
	void PopulateTreeControls();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__3FF9B7C2_F1C0_11D1_ABA6_442100C10000__INCLUDED_)
