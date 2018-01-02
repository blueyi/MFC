// hovbuttDlg.h : header file
//

#if !defined(AFX_HOVBUTTDLG_H__11557376_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
#define AFX_HOVBUTTDLG_H__11557376_628E_11D2_81B5_0020AFC24C58__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HoverButton.h"

/////////////////////////////////////////////////////////////////////////////
// CHovbuttDlg dialog

class CHovbuttDlg : public CDialog
{
// Construction
public:
	CHovbuttDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHovbuttDlg)
	enum { IDD = IDD_HOVBUTT_DIALOG };
	CHoverButton	m_button4;
	CHoverButton	m_button3;
	CHoverButton	m_button2;
	CHoverButton	m_button1;
	//}}AFX_DATA

	int m_nSelected;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHovbuttDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	int RefreshButtons(int nSelected);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHovbuttDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOVBUTTDLG_H__11557376_628E_11D2_81B5_0020AFC24C58__INCLUDED_)
