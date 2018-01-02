// ListImageDlg.h : header file
//

#if !defined(AFX_LISTIMAGEDLG_H__AA0890C0_F8CC_49D9_9CF8_6484AF28034E__INCLUDED_)
#define AFX_LISTIMAGEDLG_H__AA0890C0_F8CC_49D9_9CF8_6484AF28034E__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CListImageDlg dialog
#include "ListImageCtrl.h"

class CListImageDlg : public CDialog
{
// Construction
public:
	CListImageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CListImageDlg)
	enum { IDD = IDD_LISTIMAGE_DIALOG };
	CListImageCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CListImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTIMAGEDLG_H__AA0890C0_F8CC_49D9_9CF8_6484AF28034E__INCLUDED_)
