// ToolTipZENDlg.h : header file
//
/*
Author:     Zarembo Maxim
Country:    Belarus
City:       Minsk
e-mail:     mzarembo@iba.by
WWW:        http://maxim.z.tripod.com/ 
ICQ:        64569598
*/

#if !defined(AFX_TOOLTIPZENDLG_H__673579E5_F336_4582_99ED_0A8FF275AA8E__INCLUDED_)
#define AFX_TOOLTIPZENDLG_H__673579E5_F336_4582_99ED_0A8FF275AA8E__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolTipZENDlg dialog

class CToolTipZENDlg : public CDialog
{
// Construction
public:
	CToolTipZENDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CToolTipZENDlg)
	enum { IDD = IDD_TOOLTIPZEN_DIALOG };
	int		m_x;
	int		m_y;
	CString	m_text;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipZENDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	HWND hwndTT;      // handle to the ToolTip control	
	// struct specifying info about tool in ToolTip control
    TOOLINFO ti;
	CButton	m_but;
	bool bToolTip;

	// Generated message map functions
	//{{AFX_MSG(CToolTipZENDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLTIPZENDLG_H__673579E5_F336_4582_99ED_0A8FF275AA8E__INCLUDED_)
