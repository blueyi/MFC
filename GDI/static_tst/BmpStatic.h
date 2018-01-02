#if !defined(AFX_BMPSTATIC_H__0C7681A8_2790_4B97_8775_0A59CFD9EB0D__INCLUDED_)
#define AFX_BMPSTATIC_H__0C7681A8_2790_4B97_8775_0A59CFD9EB0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpStatic.h : header file
//

#include "MChMemBm.h"

/////////////////////////////////////////////////////////////////////////////
// CBmpStatic window

class CBmpStatic : public CStatic
{
// Construction
public:
	CBmpStatic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpStatic)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmpStatic();

	// Generated message map functions
protected:
	CFont m_fntText;
	COLORREF m_crTrans;
	MChMemBm m_bmImg;
	
public:
	//{{AFX_MSG(CBmpStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPSTATIC_H__0C7681A8_2790_4B97_8775_0A59CFD9EB0D__INCLUDED_)
