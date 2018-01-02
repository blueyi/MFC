// CxShadeButtonDemoDlg.h : header file
//

#if !defined(AFX_CXSHADEBUTTONDEMODLG_H__165779A8_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_)
#define AFX_CXSHADEBUTTONDEMODLG_H__165779A8_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCxShadeButtonDemoDlg dialog

#include "xShadeButton.h"

class CCxShadeButtonDemoDlg : public CDialog
{
// Construction
public:
	CCxShadeButtonDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCxShadeButtonDemoDlg)
	enum { IDD = IDD_CXSHADEBUTTONDEMO_DIALOG };
	CxShadeButton	m_btn13;
	CxShadeButton	m_btn12;
	CxShadeButton	m_btn11;
	CxShadeButton	m_btn9;
	CxShadeButton	m_btn8;
	CxShadeButton	m_btn6;
	CxShadeButton	m_btn7;
	CxShadeButton	m_btn5;
	CxShadeButton	m_btn4;
	CxShadeButton	m_btn3;
	CxShadeButton	m_btn2;
	CxShadeButton	m_btn10;
	CxShadeButton	m_btn1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCxShadeButtonDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCxShadeButtonDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXSHADEBUTTONDEMODLG_H__165779A8_46C9_11D5_B6C0_00E07D8144D0__INCLUDED_)
