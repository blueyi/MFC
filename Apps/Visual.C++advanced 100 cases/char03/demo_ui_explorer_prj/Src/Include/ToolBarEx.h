// ToolBarEx.h : header file
// Copyright ©1998 - Kirk Stowell
// All Rights Reserved.
//
// Email: kstowel@sprynet.com
// URL:   www.geocities.com/SiliconValley/Haven/8230
//
// You are free to use, modify and distribute this source, as long as
// it is not sold for profit, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND. The user
// agrees to hold the author(s) blameless from any or all problems that
// may arise from the use or distribution of this code.
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(TOOLBAREX_H_INCLUDED)
#define TOOLBAREX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FlatBar.h"

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx class

class CLASS_EXPORT CToolBarEx : public CFlatToolBar
{
	DECLARE_DYNAMIC(CToolBarEx)

// Construction
public:
	CToolBarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetButtonDropDown(int nID);
	void SetImageList(CImageList * pList, DWORD dwStyle);
	CWnd* InsertControl(CRuntimeClass* pClass, CString strTitle, CRect& pRect, UINT nID, DWORD dwStyle );
	void DrawNoGripper() { m_bNoGripper = true; }
	virtual ~CToolBarEx();

protected:
	void DrawBorders(CDC* pDC, CRect& rect);
	void EraseNonClient(BOOL);
	void DrawGripper(CDC & dc) const;

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarEx)
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CObList* m_pControls;
	CFont m_font;
	bool m_bNoGripper;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(TOOLBAREX_H_INCLUDED)

