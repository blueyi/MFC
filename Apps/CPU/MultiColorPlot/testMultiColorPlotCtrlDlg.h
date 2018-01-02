// testMultiColorPlotCtrlDlg.h : header file
//

#if !defined(AFX_TESTMULTICOLORPLOTCTRLDLG_H__2198BF3E_06EC_4DAA_8EA9_B92587F1B1E2__INCLUDED_)
#define AFX_TESTMULTICOLORPLOTCTRLDLG_H__2198BF3E_06EC_4DAA_8EA9_B92587F1B1E2__INCLUDED_

#include "MultiColorPlotCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//产生随机数
#define GetRandom( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))

/////////////////////////////////////////////////////////////////////////////
// CTestMultiColorPlotCtrlDlg dialog

class CTestMultiColorPlotCtrlDlg : public CDialog
{
// Construction
public:
	CTestMultiColorPlotCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestMultiColorPlotCtrlDlg)
	enum { IDD = IDD_TESTMULTICOLORPLOTCTRL_DIALOG };
	CMultiColorPlotCtrl	m_ctrlMultiColorPlot;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestMultiColorPlotCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestMultiColorPlotCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTMULTICOLORPLOTCTRLDLG_H__2198BF3E_06EC_4DAA_8EA9_B92587F1B1E2__INCLUDED_)
