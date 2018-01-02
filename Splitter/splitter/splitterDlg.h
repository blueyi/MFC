// splitterDlg.h : header file
//

#if !defined(AFX_SPLITTERDLG_H__B296B4C9_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
#define AFX_SPLITTERDLG_H__B296B4C9_D29B_11D4_AF20_00104B2CD040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ZSplitterDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CSplitterDlg dialog

class CSplitterDlg : public ZSplitterDlgImpl<CDialog>
{
// Construction
public:
	CSplitterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSplitterDlg)
	enum { IDD = IDD_SPLITTER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSplitterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERDLG_H__B296B4C9_D29B_11D4_AF20_00104B2CD040__INCLUDED_)
