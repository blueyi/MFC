/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#ifndef ABOUT_H
#define ABOUT_H

#include "xhyperlink.h"
#include "resource.h"
#include "FadeDialog.h"

#define ABOUT_BASE_CLASS CFadeDialog

//=============================================================================
class CAboutDlg : public ABOUT_BASE_CLASS
//=============================================================================
{
public:
	CAboutDlg();
	~CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CXHyperLink m_ctrlEmail;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_brush;

	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif //ABOUT_H
