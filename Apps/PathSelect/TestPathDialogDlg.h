// TestPathDialogDlg.h : header file
//

#if !defined(AFX_TESTPATHDIALOGDLG_H__C5C1396C_1275_11D4_B013_0000E8DD8DAA__INCLUDED_)
#define AFX_TESTPATHDIALOGDLG_H__C5C1396C_1275_11D4_B013_0000E8DD8DAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestPathDialogDlg dialog

class CTestPathDialogDlg : public CDialog
{
// Construction
public:
	CTestPathDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPathDialogDlg)
	enum { IDD = IDD_TESTPATHDIALOG_DIALOG };
	CEdit	m_ctrlPathName;
	CString	m_strPathName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPathDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestPathDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowser();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPATHDIALOGDLG_H__C5C1396C_1275_11D4_B013_0000E8DD8DAA__INCLUDED_)
