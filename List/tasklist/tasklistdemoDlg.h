// tasklistdemoDlg.h : header file
//

#if !defined(AFX_TASKLISTDEMODLG_H__93492612_DAC7_11D6_BC5D_A87F9E74545F__INCLUDED_)
#define AFX_TASKLISTDEMODLG_H__93492612_DAC7_11D6_BC5D_A87F9E74545F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Include custom combobox control
#include "tasklist.h"

class CTasklistdemoDlg : public CDialog
{
// Construction
public:
	CTasklistdemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTasklistdemoDlg)
	enum { IDD = IDD_TASKLISTDEMO_DIALOG };
	CTaskList m_ctrlTask;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTasklistdemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTasklistdemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddtolist();
	afx_msg void OnSelectMonth(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKLISTDEMODLG_H__93492612_DAC7_11D6_BC5D_A87F9E74545F__INCLUDED_)
