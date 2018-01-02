// CustDlgDlg.h : header file
//

#if !defined(AFX_CUSTDLGDLG_H__A02A2677_7604_44FC_BDA4_49EEED822404__INCLUDED_)
#define AFX_CUSTDLGDLG_H__A02A2677_7604_44FC_BDA4_49EEED822404__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SMButton.h"

/////////////////////////////////////////////////////////////////////////////
// CCustDlgDlg dialog

class CCustDlgDlg : public CDialog
{
// Construction
public:
	CCustDlgDlg(CWnd* pParent = NULL);	// standard constructor
	~CCustDlgDlg();

// Dialog Data
	//{{AFX_DATA(CCustDlgDlg)
	enum { IDD = IDD_CUSTDLG_DIALOG };
	CSMButton	m_btnOK;
	CSMButton	m_btnCancel;
	CSMButton	m_btnChg;
	CSMButton	m_btnAbout;
	CSMButton	m_btnOpen;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COLORREF m_clrText;
	COLORREF m_clrBkgnd;
	CBrush m_brBkgnd;
	CBrush m_brControlBkgnd1;
	CBrush m_brControlBkgnd2;
	HBITMAP m_hCat1;
	HBITMAP m_hCat2;

	// Generated message map functions
	//{{AFX_MSG(CCustDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnChg();
	afx_msg void OnBtnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTDLGDLG_H__A02A2677_7604_44FC_BDA4_49EEED822404__INCLUDED_)
