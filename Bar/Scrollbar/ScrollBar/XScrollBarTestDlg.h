// XScrollBarTestDlg.h : header file
//

#ifndef XSCROLLBARTESTDLG_H
#define XSCROLLBARTESTDLG_H


/////////////////////////////////////////////////////////////////////////////
// CXScrollBarTestDlg dialog

class CXScrollBarTestDlg : public CDialog
{
// Construction
public:
	CXScrollBarTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXScrollBarTestDlg)
	enum { IDD = IDD_XSCROLLBARTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXScrollBarTestDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON	m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXScrollBarTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonHorz();
	afx_msg void OnButtonVert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XSCROLLBARTESTDLG_H
