// ListCtrlLinkTestDlg.h : header file
//

#if !defined(AFX_LISTCTRLLINKTESTDLG_H__CB7802D6_341A_4BC2_BE6D_0E7123B74D42__INCLUDED_)
#define AFX_LISTCTRLLINKTESTDLG_H__CB7802D6_341A_4BC2_BE6D_0E7123B74D42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListCtrlLinkTestDlg dialog
#include "ListCtrlLink.h"

class CListCtrlLink;

class CListCtrlLinkTestDlg : public CDialog
{
// Construction
public:
	CListCtrlLinkTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListCtrlLinkTestDlg)
	enum { IDD = IDD_LISTCTRLLINKTEST_DIALOG };
	CListCtrlLink	m_listCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlLinkTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListCtrlLinkTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLLINKTESTDLG_H__CB7802D6_341A_4BC2_BE6D_0E7123B74D42__INCLUDED_)
