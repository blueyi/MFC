#if !defined(AFX_WINDOWLISTDLG_H__C67D43A8_F890_11D1_83BA_0000B43382FE__INCLUDED_)
#define AFX_WINDOWLISTDLG_H__C67D43A8_F890_11D1_83BA_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WindowListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWindowListDlg dialog

class CWindowListDlg : public CDialog
{
// Construction
public:
	CWindowListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWindowListDlg)
	enum { IDD = IDD_WINDOWLIST };
	CListBox	wndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWindowListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate();
	afx_msg void OnClose();
	afx_msg void OnSelchangeWindowlist();
	afx_msg void OnDblclkWindowlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWLISTDLG_H__C67D43A8_F890_11D1_83BA_0000B43382FE__INCLUDED_)
