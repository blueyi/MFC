// StaticTstDlg.h : header file
//

#if !defined(AFX_STATICTSTDLG_H__E6B2B56E_6208_4F78_B284_C6C470A485BB__INCLUDED_)
#define AFX_STATICTSTDLG_H__E6B2B56E_6208_4F78_B284_C6C470A485BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BmpStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CStaticTstDlg dialog

class CStaticTstDlg : public CDialog
{
// Construction
public:
	CStaticTstDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStaticTstDlg)
	enum { IDD = IDD_STATIC_TST_DIALOG };
	CBmpStatic	m_ctlBmpStatic;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticTstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStaticTstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICTSTDLG_H__E6B2B56E_6208_4F78_B284_C6C470A485BB__INCLUDED_)
