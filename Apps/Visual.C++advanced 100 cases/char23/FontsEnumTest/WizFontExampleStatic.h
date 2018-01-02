#if !defined(AFX_CWizFontExampleStatic_H__70AD4C44_8FDD_11D1_92BC_006097AEFD47__INCLUDED_)
#define AFX_CWizFontExampleStatic_H__70AD4C44_8FDD_11D1_92BC_006097AEFD47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WizFontExampleEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizFontExampleStatic window

class CWizFontExampleStatic : public CStatic
{
// Construction
public:
	CWizFontExampleStatic();

// Attributes
public:

// Operations
public:
	void	SetFont (LPCTSTR fontname, int pp_size, BOOL bItal, BOOL bBold, BOOL bUnder);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizFontExampleStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizFontExampleStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizFontExampleStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	CFont	m_Font;
	LOGFONT m_lf;
	CString	m_strSample;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWizFontExampleStatic_H__70AD4C44_8FDD_11D1_92BC_006097AEFD47__INCLUDED_)
