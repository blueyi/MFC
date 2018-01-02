// CGradientCtrlDemoDlg.h : header file
//

#if !defined(AFX_CGRADIENTCTRLDEMODLG_H__87C12B06_8E7D_4885_BE16_B64E41DF5AD9__INCLUDED_)
#define AFX_CGRADIENTCTRLDEMODLG_H__87C12B06_8E7D_4885_BE16_B64E41DF5AD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GradientCtrl.h"
#include "ColorButton.h"
#include "firewnd.h"

/////////////////////////////////////////////////////////////////////////////
// CGradientCtrlDemoDlg dialog

class CGradientCtrlDemoDlg : public CDialog
{
// Construction
public:
	CGradientCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGradientCtrlDemoDlg)
	enum { IDD = IDD_CGRADIENTCTRLDEMO_DIALOG };
	CEdit	m_wndQuantizationEntries;
	CComboBox	m_wndMethodCombo;
	CGradientCtrl m_wndGradientCtrl;
	CColorButton m_NewPegColour;
	CColorButton m_SelPegColour;
	CColorButton m_BackgroundColour;
	BOOL	m_UseBackground;
	float	m_SelPegPosition;
	BOOL	m_EnableQuantization;
	int		m_QuantizationEntries;
	float	m_NewPegPosition;
	BOOL	m_bShowToolTips;
	//}}AFX_DATA

	CFireWnd m_FireWnd;
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradientCtrlDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetControls();
	void UpdateFirePalette();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGradientCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg long OnSelEndOK(UINT /*lParam*/, LONG /*wParam*/);
	afx_msg void OnAddPeg();
	afx_msg void OnDelPeg();
	afx_msg void OnOpen();
	afx_msg void OnSaveas();
	afx_msg void OnChangeSelpegPosition();
	afx_msg void OnAbout();
	afx_msg void OnUseBackground();
	afx_msg void OnSelchangeMethodCombo();
	afx_msg void OnEnableQuantization();
	afx_msg void OnChangeQuantizationEntries();
	afx_msg void OnShowtooltips();
	afx_msg void OnHorizontal();
	afx_msg void OnVertical();
	afx_msg void OnRightTop();
	afx_msg void OnLeftBottom();
	//}}AFX_MSG
	afx_msg void OnNotifyChangeSelPeg(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnNotifyPegMove(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnNotifyPegMoved(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnNotifyPegRemoved(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnNotifyDoubleClickCreate(NMHDR * pNotifyStruct, LRESULT *result);
	afx_msg void OnNotifyEditPeg(NMHDR * pNotifyStruct, LRESULT *result);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGRADIENTCTRLDEMODLG_H__87C12B06_8E7D_4885_BE16_B64E41DF5AD9__INCLUDED_)
