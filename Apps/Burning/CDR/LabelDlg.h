#if !defined(AFX_LABELDLG_H__C87C0A1F_1CB4_4954_AEF7_8F6B1BA0BD80__INCLUDED_)
#define AFX_LABELDLG_H__C87C0A1F_1CB4_4954_AEF7_8F6B1BA0BD80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LabelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLabelDlg dialog

class CLabelDlg : public CDialog
{
// Construction
public:
	CLabelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLabelDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_label;
	CString	m_hint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLabelDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABELDLG_H__C87C0A1F_1CB4_4954_AEF7_8F6B1BA0BD80__INCLUDED_)
