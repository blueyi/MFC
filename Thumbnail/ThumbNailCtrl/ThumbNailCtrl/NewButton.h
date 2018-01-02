#if !defined(AFX_NEWBUTTON_H__076382F4_C277_4A00_B5B8_4D73DAE051C5__INCLUDED_)
#define AFX_NEWBUTTON_H__076382F4_C277_4A00_B5B8_4D73DAE051C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewButton window

class CNewButton : public CButton
{
// Construction
public:
	CNewButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBUTTON_H__076382F4_C277_4A00_B5B8_4D73DAE051C5__INCLUDED_)
