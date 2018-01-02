// HLinkTestDlg.h : header file
//

#if !defined(AFX_HLINKTESTDLG_H__DE0F2CC9_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_)
#define AFX_HLINKTESTDLG_H__DE0F2CC9_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_

#include "hyperlink.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHLinkTestDlg dialog

class CHLinkTestDlg : public CDialog
{
// Construction
public:
	CHLinkTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHLinkTestDlg)
	enum { IDD = IDD_HLINKTEST_DIALOG };
	CHyperLink	m_internet_link;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHLinkTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHLinkTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLINKTESTDLG_H__DE0F2CC9_ACE4_11D3_AEDD_0050BABF4197__INCLUDED_)
