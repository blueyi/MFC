// CAppBarApplicationDlg.h : header file
//

#pragma once
#include "TransparentDlg.h"

// CCAppBarApplicationDlg dialog
class CCAppBarApplicationDlg : public CDialog
{
// Construction
public:
	CCAppBarApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CAPPBARAPPLICATION_DIALOG };

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
public:
	afx_msg void OnBnClickedButton1();
	CTransparentDlg *m_TransparentDlg;
	afx_msg void OnDestroy();
};
