#if !defined(AFX_TESTDLG2_H__B296B4D3_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
#define AFX_TESTDLG2_H__B296B4D3_D29B_11D4_AF20_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg2.h : header file
//

#include "ZSplitterDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg2 dialog

class CTestDlg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestDlg2)

// Construction
public:
	CTestDlg2();
	~CTestDlg2();

// Dialog Data
	//{{AFX_DATA(CTestDlg2)
	enum { IDD = IDD_PROPPAGE_MEDIUM1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestDlg2)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  ZSplitterDlg m_mng;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG2_H__B296B4D3_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
