// ListBoxCHDemoDlg.h : header file
//

#if !defined(AFX_LISTBOXCHDEMODLG_H__ED804CA7_C5B1_11D6_8D12_004033579553__INCLUDED_)
#define AFX_LISTBOXCHDEMODLG_H__ED804CA7_C5B1_11D6_8D12_004033579553__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListBoxCHDemoDlg dialog
#include "ListBoxCH.h"
class CListBoxCHDemoDlg : public CDialog
{
// Construction
public:
	CListBoxCHDemoDlg(CWnd* pParent = NULL);	// standard constructor
	CListBoxCH			m_ListBox;
// Dialog Data
	//{{AFX_DATA(CListBoxCHDemoDlg)
	enum { IDD = IDD_LISTBOXCHDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxCHDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListBoxCHDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetSelIndex();
	afx_msg void OnSelchangeSelColorCombo();
	afx_msg void OnSelchangeBgColorCombo();
	afx_msg void OnSelchangeTextColorCombo();
	afx_msg void OnEdgeCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXCHDEMODLG_H__ED804CA7_C5B1_11D6_8D12_004033579553__INCLUDED_)
