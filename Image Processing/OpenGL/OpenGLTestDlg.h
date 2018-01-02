// OpenGLTestDlg.h : header file
//

#if !defined(AFX_OPENGLTESTDLG_H__9273E16F_C94E_4B7A_943C_73F5B11537C1__INCLUDED_)
#define AFX_OPENGLTESTDLG_H__9273E16F_C94E_4B7A_943C_73F5B11537C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COpenGLTestDlg dialog

#include "TestWnd.h"

class COpenGLTestDlg : public CDialog
{
// Construction
public:
	CTestWnd	m_wndOpenGL;
public:
	COpenGLTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COpenGLTestDlg)
	enum { IDD = IDD_OPENGLTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COpenGLTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLTESTDLG_H__9273E16F_C94E_4B7A_943C_73F5B11537C1__INCLUDED_)
