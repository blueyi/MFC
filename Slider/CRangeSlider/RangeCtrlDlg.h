// RangeCtrlDlg.h : header file
//

#if !defined(AFX_RANGECTRLDLG_H__0D573D09_9B72_4679_9262_CBAC2F3A5E7D__INCLUDED_)
#define AFX_RANGECTRLDLG_H__0D573D09_9B72_4679_9262_CBAC2F3A5E7D__INCLUDED_

#include "RangeSlider.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRangeCtrlDlg dialog

class CRangeCtrlDlg : public CDialog
{
// Construction
public:
	CRangeSlider c_RangeSlider;
	CRangeCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRangeCtrlDlg)
	enum { IDD = IDD_RANGECTRL_DIALOG };
	CButton	c_Feedback;
	CEdit	c_VisualMin;
	CEdit	c_VisualMax;
	CButton	c_VisualMinMax;
	double	m_Min;
	double	m_Max;
	double	m_Left;
	double	m_Right;
	double	m_VisualMax;
	double	m_VisualMin;
	BOOL	m_bVisualMinMax;
	BOOL	m_bInvertedMode;
	BOOL	m_bVerticalMode;
	BOOL	m_Feedback;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRangeCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRangeCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnKillfocusMax();
	afx_msg void OnKillfocusMin();
	afx_msg void OnVisualMinmax();
	afx_msg void OnKillfocusVisualminmax();
	afx_msg void OnInvertedmode();
	afx_msg void OnVerticalmode();
	afx_msg void OnKillfocusLeft();
	afx_msg void OnKillfocusRight();
	//}}AFX_MSG
	LRESULT OnRangeChange(WPARAM wParam, LPARAM /* lParam */);

	
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANGECTRLDLG_H__0D573D09_9B72_4679_9262_CBAC2F3A5E7D__INCLUDED_)
