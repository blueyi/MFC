// ExpandDialogDlg.h : header file
//

#if !defined(AFX_EXPANDDIALOGDLG_H__866E8707_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_)
#define AFX_EXPANDDIALOGDLG_H__866E8707_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExpandDialogDlg dialog

class CExpandDialogDlg : public CDialog
{
// Construction
public:
	CExpandDialogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExpandDialogDlg)
	enum { IDD = IDD_EXPANDDIALOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpandDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void EnableVisibleChildren();
	void ExtendDlg(int nResourceID,BOOL bExpand);

	// Generated message map functions
	//{{AFX_MSG(CExpandDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMoreButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPANDDIALOGDLG_H__866E8707_EBC8_11D4_AFC0_9AFBB6000000__INCLUDED_)
