// ClrGradientPrgssCtrlDlg.h : header file
//

#if !defined(AFX_CLRGRADIENTPRGSSCTRLDLG_H__597FBAE7_62C9_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CLRGRADIENTPRGSSCTRLDLG_H__597FBAE7_62C9_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClrGradientPrgssCtrlDlg dialog
#include "GradientProgressCtrl.h"

class CClrGradientPrgssCtrlDlg : public CDialog
{
// Construction
public:
	CClrGradientPrgssCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClrGradientPrgssCtrlDlg)
	enum { IDD = IDD_CLRGRADIENTPRGSSCTRL_DIALOG };
	CGradientProgressCtrl	m_cProgress;
	UINT	m_nRange;
	BOOL	m_bShowPercent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClrGradientPrgssCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	COLORREF m_clrText, m_clrBk, m_clrStart, m_clrEnd;

	// Generated message map functions
	//{{AFX_MSG(CClrGradientPrgssCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLRGRADIENTPRGSSCTRLDLG_H__597FBAE7_62C9_11D6_8F32_00E04CE76240__INCLUDED_)
