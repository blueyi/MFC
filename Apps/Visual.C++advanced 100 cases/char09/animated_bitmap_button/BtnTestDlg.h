// BtnTestDlg.h : header file
//

#if !defined(AFX_BTNTESTDLG_H__CBAD41A7_3245_11D2_8C4F_000000000000__INCLUDED_)
#define AFX_BTNTESTDLG_H__CBAD41A7_3245_11D2_8C4F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CBtnTestDlg dialog

class CBtnTestDlg : public CDialog
{
// Construction
public:
	CBtnTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBtnTestDlg)
	enum { IDD = IDD_BTNTEST_DIALOG };
	CAniButton	m_btnFree;
	CAniButton	m_btnFlag;
	CAniButton	m_btnGlobe3;
	CAniButton	m_btnGlobe2;
	CAniButton	m_btnGlobe1;
	BOOL	m_bGlobeEnabled;
	BOOL	m_bFreeEnabled;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBtnTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBtnTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnGlobeEnable();
	afx_msg void OnGlobe();
	afx_msg void OnFreeEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    BOOL SetupAniButtons();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNTESTDLG_H__CBAD41A7_3245_11D2_8C4F_000000000000__INCLUDED_)
