// MyBarLeft.h : header file
// 
// Copyright © 1998 Written by Kirk Stowell    
//		mailto:kstowel@sprynet.com 
//		http://www.geocities.com/SiliconValley/Haven/8230 
// 
// This code may be used in compiled form in any way you desire. This   
// file may be redistributed unmodified by any means PROVIDING it is    
// not sold for profit without the authors written consent, and    
// providing that this notice and the authors name and all copyright    
// notices remains intact. If the source code in this file is used in    
// any  commercial application then a statement along the lines of    
// "Portions Copyright © 1998 Kirk Stowell" must be included in    
// the startup banner, "About" box or printed documentation. An email    
// letting me know that you are using it would be nice as well. That's    
// not much to ask considering the amount of work that went into this.   
//   
// This file is provided "as is" with no expressed or implied warranty.   
// The author accepts no liability for any damage/loss of business that   
// this product may cause.   
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(MYBARLEFT_H_INCLUDED)
#define MYBARLEFT_H_INCLUDED

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CJControlBar.h"

/////////////////////////////////////////////////////////////////////////////
// CMyBarLeft class

class CMyBarLeft : public CCJControlBar
{
// Construction
public:
	CMyBarLeft();

// Attributes
public:
	CTreeCtrl  m_TreeCtrl;
	CImageList m_ImageList;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBarLeft)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyBarLeft();

// Generated message map functions
protected:
	//{{AFX_MSG(CMyBarLeft)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(MYBARLEFT_H_INCLUDED)

