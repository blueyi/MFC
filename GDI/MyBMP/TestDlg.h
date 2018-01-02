// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__E54C2554_4949_11D4_9F8F_0080C88D88FF__INCLUDED_)
#define AFX_TESTDLG_H__E54C2554_4949_11D4_9F8F_0080C88D88FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
#include "ShowStyleDlg.h"
class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor
	void SetButtons();
	CShowStyleDlg m_showDlg;
// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CString	m_bmpName;
	BYTE	m_colorG;
	BYTE	m_colorB;
	BYTE	m_colorR;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenBmp();
	afx_msg void OnUsecheck();
	afx_msg void OnBmpOrigin();
	afx_msg void OnBmpStretch();
	afx_msg void OnBmpTile();
	afx_msg void OnBackBmp();
	afx_msg void OnBackColored();
	afx_msg void OnBackNormal();
	afx_msg void OnChangeColorB();
	afx_msg void OnKillfocusColorB();
	afx_msg void OnChangeColorG();
	afx_msg void OnKillfocusColorG();
	afx_msg void OnChangeColorR();
	afx_msg void OnKillfocusColorR();
	afx_msg void OnShowDlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__E54C2554_4949_11D4_9F8F_0080C88D88FF__INCLUDED_)
