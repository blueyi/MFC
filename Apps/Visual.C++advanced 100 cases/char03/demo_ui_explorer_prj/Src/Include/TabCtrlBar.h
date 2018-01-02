// TabCtrlBar.h : header file
// This class is based on the article "Sizing TabControlBar"
// written by Dirk Clemens. My modifications marked *** KStowell
// http://www.codeguru.com/docking/sizing_tabctrl_bar.shtml
//////////////////////////////////////////////////////////////////////

#if !defined(TABCTRLBAR_H_INCLUDED)
#define TABCTRLBAR_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

typedef struct {
	CWnd *pWnd;
	char szLabel[32];
}TCB_ITEM;

#include <afxtempl.h>
#include "ControlBarEx.h"

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlBar class

class CLASS_EXPORT CTabCtrlBar : public CControlBarEx
{
	DECLARE_DYNAMIC(CTabCtrlBar)

// Construction
public:
	CTabCtrlBar();

// Attributes
public:
	CTabCtrl m_tabctrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ModifyTabStyle(DWORD dwRemove, DWORD dwAdd);
	void SetActiveView(int nNewTab);
	void SetActiveView(CRuntimeClass *pViewClass);
	void SetImageListEx( UINT nID, UINT nSz, COLORREF clr );
	void RemoveView(int nView);
	CView* GetActiveView();
	CView* GetView(int nView);
	CView* GetView(CRuntimeClass *pViewClass);
	BOOL AddView(LPCTSTR lpszLabel, CRuntimeClass *pViewClass, CCreateContext *pContext = NULL);
	virtual ~CTabCtrlBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	int				m_nActiveTab;
	int				m_nItem;
	bool			m_bEnable;
	CView*			m_pActiveView;
	CImageList		m_images;
	CToolTipCtrl*	m_tooltip;
	CList <TCB_ITEM *,TCB_ITEM *> m_views;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(TABCTRLBAR_H_INCLUDED)

