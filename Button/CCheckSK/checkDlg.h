// checkDlg.h : header file
//

#if !defined(AFX_CHECKDLG_H__CBF97C9E_CBFE_4767_AE43_E815A07E9D34__INCLUDED_)
#define AFX_CHECKDLG_H__CBF97C9E_CBFE_4767_AE43_E815A07E9D34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckDlg dialog
#include "CCheckSK.h"

class CCheckDlg : public CDialog
{
// Construction
public:
	CCheckDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckDlg)
	enum { IDD = IDD_CHECK_DIALOG };
	
    CCheckSK m_chk6;
    CCheckSK m_chk5;
    CCheckSK m_chk4;
	CCheckSK m_chk3;
	CCheckSK m_chk2;
	CCheckSK m_chk1;
    BOOL	m_chk3Val;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKDLG_H__CBF97C9E_CBFE_4767_AE43_E815A07E9D34__INCLUDED_)
