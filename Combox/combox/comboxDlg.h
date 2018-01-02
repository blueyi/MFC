// comboxDlg.h : header file
// Download by http://www.codefans.net

#if !defined(AFX_COMBOXDLG_H__2AAEF755_CD1D_42D8_9B1F_AD46434517A8__INCLUDED_)
#define AFX_COMBOXDLG_H__2AAEF755_CD1D_42D8_9B1F_AD46434517A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitmapPickerCombo.h"

/////////////////////////////////////////////////////////////////////////////
// CComboxDlg dialog

class CComboxDlg : public CDialog
{
// Construction
public:
	CComboxDlg(CWnd* pParent = NULL);	// standard constructor

	CBitmapKeyed bmready,bmstop;
	
   CBitmapPickerCombo m_Combox;

// Dialog Data
	//{{AFX_DATA(CComboxDlg)
	enum { IDD = IDD_COMBOX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComboxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOXDLG_H__2AAEF755_CD1D_42D8_9B1F_AD46434517A8__INCLUDED_)
