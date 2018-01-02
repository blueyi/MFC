// GammaManagerDlg.h : header file
//

#if !defined(AFX_GAMMAMANAGERDLG_H__67F12CB9_5AB5_467C_9F83_960EF669AFA1__INCLUDED_)
#define AFX_GAMMAMANAGERDLG_H__67F12CB9_5AB5_467C_9F83_960EF669AFA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGammaManagerDlg dialog
#include "GammaSlider.h"

class CGammaManagerDlg : public CDialog
{
// Construction
public:
	CGammaManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGammaManagerDlg)
	enum { IDD = IDD_GAMMAMANAGER_DIALOG };
	CGammaSlider	m_GammaSlider;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGammaManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CGammaManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMMAMANAGERDLG_H__67F12CB9_5AB5_467C_9F83_960EF669AFA1__INCLUDED_)
