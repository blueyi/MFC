#if !defined(AFX_TESTDLG1_H__B296B4D2_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
#define AFX_TESTDLG1_H__B296B4D2_D29B_11D4_AF20_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg1.h : header file
//

#include "ZSplitterDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg1 dialog

class CTestDlg1 : public ZSplitterDlgImpl<CPropertyPage>
{
// Construction
public:
	CTestDlg1();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg1)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg1)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG1_H__B296B4D2_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
