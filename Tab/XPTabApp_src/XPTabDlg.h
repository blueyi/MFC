/////////////////////////////////////////////////////////////////////////////
// XPTabDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XPTABDLG_H__B39AA2CC_684D_11D8_97C8_0002A522F13C__INCLUDED_)
#define AFX_XPTABDLG_H__B39AA2CC_684D_11D8_97C8_0002A522F13C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XPTabCtrl.h"
#include "CustomTabCtrl.h"
#include "TabDialog1.h"
#include "TabDialog2.h"

/////////////////////////////////////////////////////////////////////////////
// CXPTabDlg dialog
class CXPTabDlg : public CDialog
{
	HICON m_hIcon;
// Construction
public:
	CXPTabDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXPTabDlg)
	enum { IDD = IDD_XPTABAPP_DIALOG };
	CXPTabCtrl	m_tabCtrl;

	int		m_bTabExtended;
	int		m_eTabOrientation;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXPTabDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RedrawTab();
	void TabExtended(BOOL bTabExtended);
	void TabOrientation(ETabOrientation eTabOrientation);

	// Generated message map functions
	//{{AFX_MSG(CXPTabDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTabExtended();
	afx_msg void OnTabOrientation();
	//}}AFX_MSG
	afx_msg BOOL OnNeedText(UINT id, NMHDR* pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
    public:
    CCustomTabContainer m_tab;
    CTabDialog1 *m_pTabDialog1;			//child dlg
    CTabDialog2 *m_pTabDialog2;			//child dlg

};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// Helper functions
void	EnableThemeDialogTexture(HWND hwndDlg);
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_XPTABDLG_H__B39AA2CC_684D_11D8_97C8_0002A522F13C__INCLUDED_)
