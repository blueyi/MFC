#if !defined(AFX_ABOUTDLG_H__A449DF81_E75B_11D1_8E55_9E80D52A2535__INCLUDED_)
#define AFX_ABOUTDLG_H__A449DF81_E75B_11D1_8E55_9E80D52A2535__INCLUDED_

#include "CButtonST_demo.h"
#include "HyperLink.h"	// Added by ClassView
#include "BtnST.h"	// Added by ClassView

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnPaint();

	// Generated message map functions
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetLogoFont(CString Name, int nHeight = -16, int nWeight = FW_BOLD, BYTE bItalic = TRUE, BYTE bUnderline = FALSE);
	CButtonST m_btnOk;
	CFont m_fontLogo;
	CHyperLink m_EMailLink;
	CHyperLink m_HomePageLink;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTDLG_H__A449DF81_E75B_11D1_8E55_9E80D52A2535__INCLUDED_)
