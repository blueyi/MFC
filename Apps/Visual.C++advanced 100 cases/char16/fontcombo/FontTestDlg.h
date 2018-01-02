// FontTestDlg.h : header file
//

#if !defined(AFX_FONTTESTDLG_H__1B527CD7_544F_11D2_84C8_0060970C2D45__INCLUDED_)
#define AFX_FONTTESTDLG_H__1B527CD7_544F_11D2_84C8_0060970C2D45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFontTestDlg dialog

class CFontTestDlg : public CDialog
{
// Construction
public:
	CFontTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFontTestDlg)
	enum { IDD = IDD_FONTTEST_DIALOG };
	CFontCombo	m_cboFont;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFontTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTTESTDLG_H__1B527CD7_544F_11D2_84C8_0060970C2D45__INCLUDED_)
