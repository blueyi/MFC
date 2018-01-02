#if !defined(AFX_SHUTDLG_H__1639A24F_5366_4501_B9E2_17A8E3D5B4EE__INCLUDED_)
#define AFX_SHUTDLG_H__1639A24F_5366_4501_B9E2_17A8E3D5B4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShutDlg dialog

class CShutDlg : public CDialog
{
// Construction
public:
	void InitShut();
	CShutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShutDlg)
	enum { IDD = IDD_DIG_SYS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	LOGFONT			lgfont;
	CFont			font;
	CBitmapButton	m_bt_shut;
	CBitmapButton	m_bt_relogin;
	CBitmapButton	m_bt_reboot;
	// Generated message map functions
	//{{AFX_MSG(CShutDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnCancel();
	afx_msg void OnBtShutdown();
	afx_msg void OnBtRelogin();
	afx_msg void OnBtReboot();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDLG_H__1639A24F_5366_4501_B9E2_17A8E3D5B4EE__INCLUDED_)
