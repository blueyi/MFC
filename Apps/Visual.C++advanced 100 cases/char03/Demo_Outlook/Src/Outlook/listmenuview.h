#if !defined(AFX_LISTMENUVIEW_H__C989BC95_F1A5_11D1_ABA6_741400C10000__INCLUDED_)
#define AFX_LISTMENUVIEW_H__C989BC95_F1A5_11D1_ABA6_741400C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListMenuView.h : header file
//
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CListMenuView view

class CListMenuView : public CView
{
protected:
	CListMenuView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListMenuView)

// Attributes
public:
	COutlookBar	m_OutBar;
	CPagerCtrl	m_Pager;
	CFont			m_Font;
	CRect			m_pRect;

// Operations
public:
	void InitializeMenuControl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListMenuView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListMenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CListMenuView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTMENUVIEW_H__C989BC95_F1A5_11D1_ABA6_741400C10000__INCLUDED_)
