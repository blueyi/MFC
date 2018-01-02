// CNumSpinCtrlDemoDlg.h : header file
//

#if !defined(AFX_CNUMSPINCTRLDEMODLG_H__84EE85B4_0442_4099_A606_171D80A701FE__INCLUDED_)
#define AFX_CNUMSPINCTRLDEMODLG_H__84EE85B4_0442_4099_A606_171D80A701FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NumSpinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCNumSpinCtrlDemoDlg dialog

class CCNumSpinCtrlDemoDlg : public CDialog
{
// Construction
public:
	CCNumSpinCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCNumSpinCtrlDemoDlg)
	enum { IDD = IDD_CNUMSPINCTRLDEMO_DIALOG };
	CNumSpinCtrl	m_spinValue;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCNumSpinCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCNumSpinCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckTrimZeros();
	afx_msg void OnChangeEditFormattingString();
	afx_msg void OnChangeEditMaxVal();
	afx_msg void OnChangeEditMinVal();
	afx_msg void OnChangeEditNumDecimals();
	afx_msg void OnChangeEditPos();
	afx_msg void OnRadioFormatString();
	afx_msg void OnRadioNumDecimals();
	afx_msg void OnChangeEditDelta();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

/// Attributes
protected:
	void UpdateValue();
	void EnableFormatStringControls (BOOL bEnable);
//	double m_MinVal, m_MaxVal, m_Pos, m_Delta;
//	CString m_strFormat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNUMSPINCTRLDEMODLG_H__84EE85B4_0442_4099_A606_171D80A701FE__INCLUDED_)
