// TPWndDlg.h : header file
// Download by http://www.codefans.net

#if !defined(AFX_TPWNDDLG_H__D969BC6E_D5C5_4389_857A_B370662CE3F1__INCLUDED_)
#define AFX_TPWNDDLG_H__D969BC6E_D5C5_4389_857A_B370662CE3F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TPWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTPWndDlg dialog

class CTPWndDlg : public CDialog
{
// Construction
public:
	CTPWndDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTPWndDlg)
	enum { IDD = IDD_TPWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPWndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTPWndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TPWNDDLG_H__D969BC6E_D5C5_4389_857A_B370662CE3F1__INCLUDED_)
