// Wizard.h : header file
//

#if !defined(AFX_WIZARD_H__4EC7FCAF_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
#define AFX_WIZARD_H__4EC7FCAF_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "panel1.h"
#include "panel2.h"
#include "panel3.h"
#include "panel4.h"

/////////////////////////////////////////////////////////////////////////////
// CWizard

class CWizard : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizard)

// Construction
public:
	CWizard(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizard(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard)
	public:
	virtual int DoModal();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizard();

protected:
    CPanel1 m_panel1;
    CPanel2 m_panel2;
    CPanel3 m_panel3;
    CPanel4 m_panel4;

	// Generated message map functions
	//{{AFX_MSG(CWizard)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARD_H__4EC7FCAF_25D4_11D3_8D3B_9BE7BCEB1D3D__INCLUDED_)
