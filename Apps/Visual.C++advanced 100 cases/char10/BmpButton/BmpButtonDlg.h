// BmpButtonDlg.h : header file
//

#if !defined(AFX_BMPBUTTONDLG_H__8CDDBF09_E0D2_11D4_AF89_FE799D000000__INCLUDED_)
#define AFX_BMPBUTTONDLG_H__8CDDBF09_E0D2_11D4_AF89_FE799D000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBmpButtonDlg dialog

class CBmpButtonDlg : public CDialog
{
// Construction
public:
	CBmpButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBmpButtonDlg)
	enum { IDD = IDD_BMPBUTTON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmpButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	//wb add down
	CBitmapButton button1;
	CBitmapButton button2;
	//wb add up
	// Generated message map functions
	//{{AFX_MSG(CBmpButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBUTTONDLG_H__8CDDBF09_E0D2_11D4_AF89_FE799D000000__INCLUDED_)
