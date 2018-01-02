// MacButtonsDlg.h : header file
//

#include "MacButton.h"
#include "MacCheckBox.h"
#include "MacRadioButton.h"

#if !defined(AFX_MACBUTTONSDLG_H__D503030B_B171_11D3_90F9_0020AFBC499D__INCLUDED_)
#define AFX_MACBUTTONSDLG_H__D503030B_B171_11D3_90F9_0020AFBC499D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMacButtonsDlg dialog

class CMacButtonsDlg : public CDialog
{
// Construction
public:
	CMacButtonsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMacButtonsDlg)
	enum { IDD = IDD_MACBUTTONS_DIALOG };
	CMacButton	m_btnMacOK;
	CMacCheckBox	m_chkMac2;
	CMacCheckBox	m_chkMac1;
	CMacRadioButton	m_rdoMac1;
	CMacButton	m_btnMac;
	//}}AFX_DATA
	CMacRadioButton	m_rdoMac2;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacButtonsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMacButtonsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MACBUTTONSDLG_H__D503030B_B171_11D3_90F9_0020AFBC499D__INCLUDED_)
