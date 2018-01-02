// MRUComboTestDlg.h : header file
//

#if !defined(AFX_MRUCOMBOTESTDLG_H__BDE24F09_4632_11D2_9505_D07F50C10000__INCLUDED_)
#define AFX_MRUCOMBOTESTDLG_H__BDE24F09_4632_11D2_9505_D07F50C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "mrucombo.h"

/////////////////////////////////////////////////////////////////////////////
// CMRUComboTestDlg dialog

class CMRUComboTestDlg : public CDialog
{
// Construction
public:
	CMRUComboTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMRUComboTestDlg)
	enum { IDD = IDD_MRUCOMBOTEST_DIALOG };
	CMRUComboBox	m_combo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMRUComboTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMRUComboTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnGetSize();
	afx_msg void OnChangeMru();
	afx_msg void OnClearMru();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MRUCOMBOTESTDLG_H__BDE24F09_4632_11D2_9505_D07F50C10000__INCLUDED_)
