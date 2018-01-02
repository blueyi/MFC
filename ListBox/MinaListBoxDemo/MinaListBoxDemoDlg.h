// MinaListBoxDemoDlg.h : header file
//

#if !defined(AFX_MINALISTBOXDEMODLG_H__65C10964_3CBE_457A_B59C_60A208EA89F8__INCLUDED_)
#define AFX_MINALISTBOXDEMODLG_H__65C10964_3CBE_457A_B59C_60A208EA89F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMinaListBoxDemoDlg dialog
#include "OwnerDrawListBox.h"

class CMinaListBoxDemoDlg : public CDialog
{
// Construction
public:
	CMinaListBoxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMinaListBoxDemoDlg)
	enum { IDD = IDD_MINALISTBOXDEMO_DIALOG };
	COwnerDrawListBox	m_OwnerListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinaListBoxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMinaListBoxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINALISTBOXDEMODLG_H__65C10964_3CBE_457A_B59C_60A208EA89F8__INCLUDED_)
