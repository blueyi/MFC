// CHexEditDemoDlg.h : header file
//

#if !defined(AFX_CHEXEDITDEMODLG_H__F908926B_65ED_4D2A_8786_B2C467834AA0__INCLUDED_)
#define AFX_CHEXEDITDEMODLG_H__F908926B_65ED_4D2A_8786_B2C467834AA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCHexEditDemoDlg dialog
#include "HexEdit.h"

class CCHexEditDemoDlg : public CDialog
{
// Construction
public:
	CCHexEditDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCHexEditDemoDlg)
	enum { IDD = IDD_CHEXEDITDEMO_DIALOG };
	CHexEdit	m_cData;
	CHexEdit	m_cLength;
	CHexEdit	m_cAddress;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCHexEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCHexEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHEXEDITDEMODLG_H__F908926B_65ED_4D2A_8786_B2C467834AA0__INCLUDED_)
