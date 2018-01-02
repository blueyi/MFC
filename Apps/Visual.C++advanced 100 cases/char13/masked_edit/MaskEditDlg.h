// MaskEditDlg.h : header file
//

#if !defined(AFX_MASKEDITDLG_H__8F2BD4D6_6425_11D2_96B4_00105A08E437__INCLUDED_)
#define AFX_MASKEDITDLG_H__8F2BD4D6_6425_11D2_96B4_00105A08E437__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NewMaskEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CMaskEditDlg dialog

class CMaskEditDlg : public CDialog
{
// Construction
public:
	CMaskEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMaskEditDlg)
	enum { IDD = IDD_MASKEDIT_DIALOG };
	CEdit	m_editMaskData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMaskEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	NewMaskEdit m_maskEdit;

	// Generated message map functions
	//{{AFX_MSG(CMaskEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonShowtext();
	afx_msg void OnButtonGetwintext();
	afx_msg void OnButtonNewMask();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MASKEDITDLG_H__8F2BD4D6_6425_11D2_96B4_00105A08E437__INCLUDED_)
