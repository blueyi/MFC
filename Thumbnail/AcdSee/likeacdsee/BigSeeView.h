// BigSeeView.h : interface of the CBigSeeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIGSEEVIEW_H__65FC334D_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_BIGSEEVIEW_H__65FC334D_C244_11D6_AFCA_001088A02FAC__INCLUDED_

#include "BigSeeDoc.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBigSeeView : public CListView
{
protected: // create from serialization only
	CBigSeeView();
	DECLARE_DYNCREATE(CBigSeeView)
		
// Attributes
public:
	CBigSeeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigSeeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnDragLeave();
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_strFilePath;
    CString m_strFileName;
	CString m_strFileExt;
	CImageList m_ilFile;
	CImageList m_ilFolder;
	//CImageList*m_pImageList;
	virtual ~CBigSeeView();
	BOOL IsHaveImage;
	void EnumFiles();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBigSeeView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BigSeeView.cpp
inline CBigSeeDoc* CBigSeeView::GetDocument()
   { return (CBigSeeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGSEEVIEW_H__65FC334D_C244_11D6_AFCA_001088A02FAC__INCLUDED_)
