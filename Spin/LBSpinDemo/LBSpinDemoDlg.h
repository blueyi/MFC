// LBSpinDemoDlg.h : header file
//

#if !defined(AFX_LBSPINDEMODLG_H__16B8B6E7_C905_11D3_AA40_008048EAE3F5__INCLUDED_)
#define AFX_LBSPINDEMODLG_H__16B8B6E7_C905_11D3_AA40_008048EAE3F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LBSpinButtonCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CLBSpinDemoDlg dialog

class CLBSpinDemoDlg : public CDialog
{
// Construction
public:
	CLBSpinDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLBSpinDemoDlg)
	enum { IDD = IDD_LBSPINDEMO_DIALOG };
	CLBSpinButtonCtrl	m_LBSpinBtnCtrl_U_HOR;
	CSpinButtonCtrl	m_SpinBtnCtrl;
	CLBSpinButtonCtrl	m_LBSpinBtnCtrl_U;
	CLBSpinButtonCtrl	m_LBSpinBtnCtrl_L;
	CLBSpinButtonCtrl	m_LBSpinBtnCtrl_R;
	int		m_nBuddy4;
	int		m_nBuddy1;
	int		m_nBuddy2;
	int		m_nBuddy3;
	int		m_nBuddy5;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBSpinDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLBSpinDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBSPINDEMODLG_H__16B8B6E7_C905_11D3_AA40_008048EAE3F5__INCLUDED_)
