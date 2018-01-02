// NumericEditTestDlg.h : header file
//

#pragma once
#include "afxwin.h"

#include "NumericEdit.h"


// CNumericEditTestDlg dialog
class CNumericEditTestDlg : public CDialog
{
// Construction
public:
	CNumericEditTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NUMERICEDITTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CEdit m_editText;
	CEdit m_editNumber;
	CNumericEdit m_editNumeric;
};
