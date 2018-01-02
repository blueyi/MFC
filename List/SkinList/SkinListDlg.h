// SkinListDlg.h : header file
//

#if !defined(AFX_SKINLISTDLG_H__526E3261_90F4_4C3C_8FFD_C77EEE12FAF3__INCLUDED_)
#define AFX_SKINLISTDLG_H__526E3261_90F4_4C3C_8FFD_C77EEE12FAF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SkinListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CSkinListDlg dialog

class CSkinListDlg : public CDialog
{
// Construction
public:
	CSkinListDlg(CWnd* pParent = NULL);	// standard constructor
	CFont font;



// Dialog Data
	//{{AFX_DATA(CSkinListDlg)
	enum { IDD = IDD_SKINLIST_DIALOG };
	CSkinListCtrl	m_SkinList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSkinListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEndtrackSkinList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINLISTDLG_H__526E3261_90F4_4C3C_8FFD_C77EEE12FAF3__INCLUDED_)
