#if !defined(AFX_DEMOTTDLG_H__46F5811C_3EEB_11D2_8FDB_000000000000__INCLUDED_)
#define AFX_DEMOTTDLG_H__46F5811C_3EEB_11D2_8FDB_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DemoTTDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDemoTTDlg dialog
#include "ToolTipWnd.h"

class CDemoTTDlg : public CDialog
{
// Construction
public:
	CDemoTTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoTTDlg)
	enum { IDD = IDD_DEMOTTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CToolTipWnd m_bttWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoTTDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDemoTTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOTTDLG_H__46F5811C_3EEB_11D2_8FDB_000000000000__INCLUDED_)
