#if !defined(AFX_WIZFONTSIZESCOMBOBOX_H__70AD4C43_8FDD_11D1_92BC_006097AEFD47__INCLUDED_)
#define AFX_WIZFONTSIZESCOMBOBOX_H__70AD4C43_8FDD_11D1_92BC_006097AEFD47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WizFontSizesComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizFontSizesComboBox window
#include "WizFontsEnumerator.h"

class CWizFontSizesComboBox : public CComboBox
{
// Construction
public:
	CWizFontSizesComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizFontSizesComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizFontSizesComboBox();

	void	Initialize (const CWizFontsEnumerator::Font* font);
	int		GetCurrentSize();
	// Generated message map functions
protected:
	//{{AFX_MSG(CWizFontSizesComboBox)
	afx_msg int OnCompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZFONTSIZESCOMBOBOX_H__70AD4C43_8FDD_11D1_92BC_006097AEFD47__INCLUDED_)
