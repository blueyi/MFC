#if !defined(AFX_WIZFONTSCRIPTSCOMBOBOX_H__9F86BB83_8CED_11D1_BBB1_444553540000__INCLUDED_)
#define AFX_WIZFONTSCRIPTSCOMBOBOX_H__9F86BB83_8CED_11D1_BBB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WizFontScriptsComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizFontScriptsComboBox window
#include "WizFontsEnumerator.h"

class CWizFontScriptsComboBox : public CComboBox
{
// Construction
public:
	CWizFontScriptsComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizFontScriptsComboBox)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizFontScriptsComboBox();

	void	Initialize (const CWizFontsEnumerator::Font* font);
	// Generated message map functions
protected:
	//{{AFX_MSG(CWizFontScriptsComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZFONTSCRIPTSCOMBOBOX_H__9F86BB83_8CED_11D1_BBB1_444553540000__INCLUDED_)
