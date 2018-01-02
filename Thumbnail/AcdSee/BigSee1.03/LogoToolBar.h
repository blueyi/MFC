#if !defined(AFX_LOGOTOOLBAR_H__DC102E85_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_LOGOTOOLBAR_H__DC102E85_D246_11D6_AFCA_001088A02FAC__INCLUDED_

#include "Logo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogoToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoToolBar window

class CLogoToolBar : public CToolBar//CToolBarCtrl
{
// Construction
public:
	CLogoToolBar();

// Attributes
public:
	CLogo m_Logo;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLogoToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogoToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGOTOOLBAR_H__DC102E85_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
