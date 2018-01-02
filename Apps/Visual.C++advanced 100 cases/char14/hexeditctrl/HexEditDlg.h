// HexEditDlg.h : header file
//

#if !defined(AFX_HEXEDITDLG_H__CF147E50_214B_11D2_B9F9_0000E829B15A__INCLUDED_)
#define AFX_HEXEDITDLG_H__CF147E50_214B_11D2_B9F9_0000E829B15A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHexEditDlg dialog
#include "hexeditctrl.h"

class CHexEditDlg : public CDialog
{
// Construction
public:
	CHexEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHexEditDlg)
	enum { IDD = IDD_HEXEDIT_DIALOG };
	CSliderCtrl	m_slider;
	CHexEdit	m_Edit;
	BOOL	m_address;
	BOOL	m_hex;
	BOOL	m_ascii;
	BOOL	m_48;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHexEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHexEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEXEDITDLG_H__CF147E50_214B_11D2_B9F9_0000E829B15A__INCLUDED_)
