// DemoListDlg.h : header file
//

#if !defined(AFX_DEMOLISTDLG_H__3683EBB5_DB94_4A46_A4F9_9B1E11FF8D24__INCLUDED_)
#define AFX_DEMOLISTDLG_H__3683EBB5_DB94_4A46_A4F9_9B1E11FF8D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include "ListCtrlCl.h"
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoListDlg dialog

class CDemoListDlg : public CDialog
{
// Construction
public:
	CDemoListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoListDlg)
	enum { IDD = IDD_DEMOLIST_DIALOG };
	CListCtrlCl	m_ListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOLISTDLG_H__3683EBB5_DB94_4A46_A4F9_9B1E11FF8D24__INCLUDED_)
