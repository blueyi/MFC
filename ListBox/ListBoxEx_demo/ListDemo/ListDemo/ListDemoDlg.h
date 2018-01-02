// ListDemoDlg.h : header file
//

#if !defined(AFX_LISTDEMODLG_H__E503C82A_836A_11D5_AD87_8686F2D82715__INCLUDED_)
#define AFX_LISTDEMODLG_H__E503C82A_836A_11D5_AD87_8686F2D82715__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListDemoDlg dialog
#include "ListBoxEx.h"
class CListDemoDlg : public CDialog
{
// Construction
public:

	CListDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListDemoDlg)
	enum { IDD = IDD_LISTDEMO_DIALOG };
	CListBoxEx	m_DemoList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTDEMODLG_H__E503C82A_836A_11D5_AD87_8686F2D82715__INCLUDED_)
