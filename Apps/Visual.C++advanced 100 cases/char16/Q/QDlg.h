// QDlg.h : header file
//

#if !defined(AFX_QDLG_H__9BBB0D1B_4EC1_11D2_8697_0040055C08D9__INCLUDED_)
#define AFX_QDLG_H__9BBB0D1B_4EC1_11D2_8697_0040055C08D9__INCLUDED_

#include "QComboBox.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CQDlg dialog

class CQDlg : public CDialog
{
// Construction
public:
	virtual  ~CQDlg();
	static CStringArray m_arItems[5];
	static LPCTSTR Line(int iLine, LPARAM& lParamItem, LPARAM lParam);
	CQComboBox* m_pCombo[5];
	CQDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CQDlg)
	enum { IDD = IDD_Q_DIALOG };
	CComboBox	m_test;
	CEdit	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CQDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QDLG_H__9BBB0D1B_4EC1_11D2_8697_0040055C08D9__INCLUDED_)
