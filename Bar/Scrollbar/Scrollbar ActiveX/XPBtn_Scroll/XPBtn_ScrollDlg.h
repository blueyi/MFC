// XPBtn_ScrollDlg.h : header file
//

#if !defined(AFX_XPBTN_SCROLLDLG_H__D34F5C9D_36A1_4B3E_87E1_58DFF3DF861A__INCLUDED_)
#define AFX_XPBTN_SCROLLDLG_H__D34F5C9D_36A1_4B3E_87E1_58DFF3DF861A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXPBtn_ScrollDlg dialog

class CXPBtn_ScrollDlg : public CDialog
{
// Construction
public:
	void GetWinVersion();
	enum WinVersion {WIN_UNKNOWN,WIN_95,WIN_98,WIN_ME,WIN_NT351,WIN_NT40,WIN_2000,WIN_XP}; 
    int  m_nWinVersion;
	CXPBtn_ScrollDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CXPBtn_ScrollDlg)
	enum { IDD = IDD_XPBTN_SCROLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPBtn_ScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXPBtn_ScrollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickOk();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XPBTN_SCROLLDLG_H__D34F5C9D_36A1_4B3E_87E1_58DFF3DF861A__INCLUDED_)
