// TreeHelperTestDlg.h : header file
//

#if !defined(AFX_TREEHELPERTESTDLG_H__5DD969D7_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
#define AFX_TREEHELPERTESTDLG_H__5DD969D7_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EditHelper.h"

/////////////////////////////////////////////////////////////////////////////
// CTreeHelperTestDlg dialog

class CTreeHelperTestDlg : public CDialog
{
// Construction
public:
	CTreeHelperTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTreeHelperTestDlg)
	enum { IDD = IDD_TREEHELPERTEST_DIALOG };
	CEditHelper	m_oEdit2;
	CEditHelper	m_oEdit1;
	CString	m_sSeparator1;
	CString	m_sSeparator2;
	CString	m_sEdit1;
	CString	m_sEdit2;
	BOOL	m_bBitmap2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeHelperTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTreeHelperTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEHELPERTESTDLG_H__5DD969D7_38CB_11D2_8F85_0060B0ECF89C__INCLUDED_)
