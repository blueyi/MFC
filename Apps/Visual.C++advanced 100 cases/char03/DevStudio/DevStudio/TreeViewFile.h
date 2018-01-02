#if !defined(AFX_TREEVIEWFILE_H__C73CC5D8_5B91_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_TREEVIEWFILE_H__C73CC5D8_5B91_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeViewFile.h : header file
//

#include <afxcview.h>

/////////////////////////////////////////////////////////////////////////////
// CTreeViewFile view

class CTreeViewFile : public CTreeView
{
protected:
	CTreeViewFile();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTreeViewFile)

// Attributes
public:
	CTreeCtrl* m_TreeCtrl;
	CImageList m_ImageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeViewFile)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTreeViewFile();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeViewFile)
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVIEWFILE_H__C73CC5D8_5B91_11D2_AB9F_441100C10000__INCLUDED_)
