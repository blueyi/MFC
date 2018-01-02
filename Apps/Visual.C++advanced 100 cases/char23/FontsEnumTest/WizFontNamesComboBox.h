#if !defined(AFX_WIZFONTNAMESCOMBOBOX_H__9F86BB82_8CED_11D1_BBB1_444553540000__INCLUDED_)
#define AFX_WIZFONTNAMESCOMBOBOX_H__9F86BB82_8CED_11D1_BBB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WizFontNamesComboBox.h : header file
//

#include "WizFontsEnumerator.h"

/////////////////////////////////////////////////////////////////////////////
// CWizFontNamesComboBox window

class CWizFontNamesComboBox : public CComboBox
{
// Construction
public:
	CWizFontNamesComboBox();

// Attributes
public:

// Operations
public:
	void	Initialize(const CWizFontsEnumerator& fonts);
	const CWizFontsEnumerator::Font* GetCurrentFont(const CWizFontsEnumerator& fonts);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizFontNamesComboBox)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizFontNamesComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizFontNamesComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZFONTNAMESCOMBOBOX_H__9F86BB82_8CED_11D1_BBB1_444553540000__INCLUDED_)
