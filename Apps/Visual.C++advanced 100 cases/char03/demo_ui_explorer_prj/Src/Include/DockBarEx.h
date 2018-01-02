// DockBarEx.h : header file
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

#if !defined(DOCKBAREX_H_INCLUDED)
#define DOCKBAREX_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxpriv.h>

// nDockBarMap
const DWORD nDockBarMap[4][2] =
{
	{ AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
	{ AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
	{ AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
	{ AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};

/////////////////////////////////////////////////////////////////////////////
// CDockBarEx class

class CDockBarEx : public CDockBar
{
	DECLARE_DYNAMIC(CDockBarEx)

// Construction
public:
	CDockBarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockBarEx)
	public:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockBarEx();

// Generated message map functions
protected:
	//{{AFX_MSG(CDockBarEx)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(DOCKBAREX_H_INCLUDED)

