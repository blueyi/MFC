// FlatComboDlg.h : header file
//

#if !defined(AFX_FLATCOMBODLG_H__3422A0B9_4F3A_11D2_957B_0040053E0F5B__INCLUDED_)
#define AFX_FLATCOMBODLG_H__3422A0B9_4F3A_11D2_957B_0040053E0F5B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "FlatComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CFlatComboDlg dialog

class CFlatComboDlg : public CDialog
{
// Construction
public:
	CFlatComboDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlatComboDlg)
	enum { IDD = IDD_FLATCOMBO_DIALOG };
	CFlatComboBox	m_Combo3;
	CFlatComboBox	m_Combo2;
	CFlatComboBox	m_Combo1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatComboDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFlatComboDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATCOMBODLG_H__3422A0B9_4F3A_11D2_957B_0040053E0F5B__INCLUDED_)
