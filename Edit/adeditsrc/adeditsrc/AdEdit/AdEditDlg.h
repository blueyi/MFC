// AdEditDlg.h : header file
//

#if !defined(AFX_ADEDITDLG_H__D9B7A0BC_24AC_41A2_B3A2_F7A0F2E538AA__INCLUDED_)
#define AFX_ADEDITDLG_H__D9B7A0BC_24AC_41A2_B3A2_F7A0F2E538AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CAdEditDlg dialog

class CAdEditDlg : public CDialog
{
// Construction
public:
	CAdEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdEditDlg)
	enum { IDD = IDD_ADEDIT_DIALOG };
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CMyEdit	m_MyEdit;
	// Generated message map functions
	//{{AFX_MSG(CAdEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnsub();
	afx_msg void OnBtnunsub();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADEDITDLG_H__D9B7A0BC_24AC_41A2_B3A2_F7A0F2E538AA__INCLUDED_)
