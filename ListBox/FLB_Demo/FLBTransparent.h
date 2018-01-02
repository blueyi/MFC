#if !defined(AFX_FLBTRANSPARENT_H__082B6446_33B4_4F2E_8FE0_B76E9DB57093__INCLUDED_)
#define AFX_FLBTRANSPARENT_H__082B6446_33B4_4F2E_8FE0_B76E9DB57093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FLBTransparent.h : header file
//
#include "FontListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CFLBTransparent window

class CFLBTransparent : public CFontListBox
{
// Construction
public:
	CFLBTransparent();
	CFLBTransparent(DWORD dwStyleFlags, LPCTSTR lpszMruListName=NULL);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFLBTransparent)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFLBTransparent();
	virtual COLORREF OnColorHighlightText();
	virtual COLORREF OnColorText();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFLBTransparent)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLBTRANSPARENT_H__082B6446_33B4_4F2E_8FE0_B76E9DB57093__INCLUDED_)
