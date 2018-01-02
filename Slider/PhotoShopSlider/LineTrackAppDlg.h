// LineTrackAppDlg.h : header file
//

#if !defined(AFX_LINETRACKAPPDLG_H__789BC138_2EC6_47B4_BD86_B09F4BD34D02__INCLUDED_)
#define AFX_LINETRACKAPPDLG_H__789BC138_2EC6_47B4_BD86_B09F4BD34D02__INCLUDED_
#include "LineTrackBar.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLineTrackAppDlg dialog

class CLineTrackAppDlg : public CDialog
{
// Construction
public:
	CLineTrackAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLineTrackAppDlg)
	enum { IDD = IDD_LINETRACKAPP_DIALOG };
	CSignEdit	m_wndEdit5;
	CSignEdit	m_wndEdit4;
	CSignEdit	m_wndEdit3;
	CSignEdit	m_wndEdit2;
	CSignEdit	m_wndEdit1;
	CString	m_strNum1;
	CString	m_strNum2;
	CString	m_strNum3;
	CString	m_strNum4;
	CString	m_strNum5;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineTrackAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CLineTrackBar m_wndLineTrackBar1;
	CLineTrackBar m_wndLineTrackBar2;
	CLineTrackBar m_wndLineTrackBar3;
	CLineTrackBar m_wndLineTrackBar4;
	CLineTrackBar m_wndLineTrackBar5;

	// Generated message map functions
	//{{AFX_MSG(CLineTrackAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nNum1;
	int m_nNum2;
	int m_nNum3;
	int m_nNum4;
	int m_nNum5;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINETRACKAPPDLG_H__789BC138_2EC6_47B4_BD86_B09F4BD34D02__INCLUDED_)
