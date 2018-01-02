// ControlBarEx.h : header file
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

#if !defined(CONTROLBAREX_H_INCLUDED)
#define CONTROLBAREX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Sizecbar.h"
#include "FlatButton.h"

/////////////////////////////////////////////////////////////////////////////
// CControlBarEx class

class CLASS_EXPORT CControlBarEx : public CSizingControlBar
{
	DECLARE_DYNAMIC(CControlBarEx)

// Construction
public:
	CControlBarEx();

// Attributes
public:
	CFlatButton  m_btnClose;
	CFlatButton  m_btnMinim;
	CImageList   m_imageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlBarEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetMenuID(UINT nID) { m_menuID = nID; }
	UINT GetMenuID() { return m_menuID; }
	virtual ~CControlBarEx();

protected:
	COLORREF	 m_clrHilite;
	COLORREF	 m_clrShadow;
	COLORREF	 m_clrButton;
	CToolTipCtrl m_tooltip;
	UINT		 m_menuID;

	CRect GetButtonRect();
	CRect GetGripperRect();
	void DrawGripper();
	bool IsOrientHorz() { return(m_dwStyle & CBRS_ORIENT_HORZ) ? true:false; }
	void OnButtonClose();
	void OnUpdateButtonClose(CCmdUI* pCmdUI);
	void OnButtonMinimize();
	void OnUpdateButtonMinimize(CCmdUI* pCmdUI);

// Generated message map functions
protected:
	//{{AFX_MSG(CControlBarEx)
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(CONTROLBAREX_H_INCLUDED)

