// CShutDlg.h : header file
//

#if !defined(AFX_CSHUTDLG_H__69E27F3E_A170_4D4A_A8CD_E84AF472FD0A__INCLUDED_)
#define AFX_CSHUTDLG_H__69E27F3E_A170_4D4A_A8CD_E84AF472FD0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCShutDlg dialog

class CCShutDlg : public CDialog
{
// Construction
public:
	CCShutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCShutDlg)
	enum { IDD = IDD_CSHUT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCShutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCShutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSHUTDLG_H__69E27F3E_A170_4D4A_A8CD_E84AF472FD0A__INCLUDED_)
