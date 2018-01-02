#ifndef __SPLITTAB_H_
#define __SPLITTAB_H_

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "wndTab.h"
//class CwndTab;

class CsplitterTabWnd : public CSplitterWnd
{
	DECLARE_DYNCREATE(CsplitterTabWnd)
public:
	CsplitterTabWnd();           
	virtual ~CsplitterTabWnd();

// Attributes
public:
   CwndTab m_wndTab;

// Get/Set
public:

// Operations
public:
	BOOL Create( CWnd* pwndParent, CCreateContext* pContext );

// Overrides
public:
   virtual void RecalcLayout();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CsplitterTabWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CsplitterTabWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
