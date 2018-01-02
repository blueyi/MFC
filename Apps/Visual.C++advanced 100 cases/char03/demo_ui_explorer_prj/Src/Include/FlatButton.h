// FlatButton.h : header file
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

#if !defined(FLATBUTTON_H_INCLUDED)
#define FLATBUTTON_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFlatButton class

class CLASS_EXPORT CFlatButton : public CButton
{
	DECLARE_DYNAMIC(CFlatButton)

// Construction
public:
	CFlatButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void SetIcon(HICON hIcon,CSize cSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DisableFlatLook();
	virtual ~CFlatButton();

// Generated message map functions
protected:
	//{{AFX_MSG(CFlatButton)
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	COLORREF	m_clrHilite;
	COLORREF	m_clrShadow;
	COLORREF    m_clrDkShad;
	COLORREF	m_clrButton;
	COLORREF	m_clrMask;
	CSize       m_cSize;
	CRect		m_rcItem;
	UINT		m_nState;
	bool		m_bLBtnDown;
	bool		m_bFlatLook;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(FLATBUTTON_H_INCLUDED)

