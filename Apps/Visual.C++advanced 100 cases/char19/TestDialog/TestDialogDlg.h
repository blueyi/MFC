// TestDialogDlg.h : header file
//

#if !defined(AFX_TESTDIALOGDLG_H__CCAACD77_1F93_11D2_864F_0040055C08D9__INCLUDED_)
#define AFX_TESTDIALOGDLG_H__CCAACD77_1F93_11D2_864F_0040055C08D9__INCLUDED_

#include "SheetsDialog.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDialogDlg dialog

class CTestDialogDlg : public CDialog
{
// Construction
public:
	CSheetsDialog sheet;
	CTestDialogDlg(CWnd* pParent = NULL);	// standard constructor
	CDialog d1,d2,d3;
	

// Dialog Data
	//{{AFX_DATA(CTestDialogDlg)
	enum { IDD = IDD_TESTDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOGDLG_H__CCAACD77_1F93_11D2_864F_0040055C08D9__INCLUDED_)
