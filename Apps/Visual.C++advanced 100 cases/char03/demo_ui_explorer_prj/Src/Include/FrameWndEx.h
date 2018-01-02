// FrameWndEx.h : header file
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

#if !defined(FRAMEWNDEX_H_INCLUDED)
#define FRAMEWNDEX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFrameWndEx class

class CLASS_EXPORT CFrameWndEx : public CFrameWnd
{
	DECLARE_DYNAMIC(CFrameWndEx)

// Construction
public:
	CFrameWndEx();

// Attributes
public:

// Operations
public:
	void DockControlBarLeftOf(CControlBar* Bar, CControlBar* LeftOf);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameWndEx)
	public:
	virtual void EnableDocking(DWORD dwDockStyle);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameWndEx();

// Generated message map functions
protected:
	//{{AFX_MSG(CFrameWndEx)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(FRAMEWNDEX_H_INCLUDED)

