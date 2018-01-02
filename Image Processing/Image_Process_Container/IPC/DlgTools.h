#if !defined(AFX_DLGTOOLS_H__8355EE35_9E9C_4D2E_839F_2EC4CC71EC2D__INCLUDED_)
#define AFX_DLGTOOLS_H__8355EE35_9E9C_4D2E_839F_2EC4CC71EC2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTools.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTools dialog

class CDlgTools : public CDialog
{
// Construction
public:
	CDlgTools(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTools)
	enum { IDD = IDD_DLG_TOOLS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTools)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTools)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTOOLS_H__8355EE35_9E9C_4D2E_839F_2EC4CC71EC2D__INCLUDED_)
