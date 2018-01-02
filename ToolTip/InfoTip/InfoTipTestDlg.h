// InfoTipTestDlg.h : header file
//

#if !defined(AFX_INFOTIPTESTDLG_H__9819F5CE_73FD_4A2C_95E6_4059F539EED7__INCLUDED_)
#define AFX_INFOTIPTESTDLG_H__9819F5CE_73FD_4A2C_95E6_4059F539EED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XInfoTip.h"

/////////////////////////////////////////////////////////////////////////////
// CInfoTipTestDlg dialog

class CInfoTipTestDlg : public CDialog
{
// Construction
public:
	CInfoTipTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoTipTestDlg)
	enum { IDD = IDD_INFOTIPTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoTipTestDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	CXInfoTip		m_Tip;

	HICON			m_hIcon1;
	HICON			m_hIcon2;
	HICON			m_hIcon3;

	CFont			m_Font;

	// Generated message map functions
	//{{AFX_MSG(CInfoTipTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOTIPTESTDLG_H__9819F5CE_73FD_4A2C_95E6_4059F539EED7__INCLUDED_)
