#if !defined(AFX_FILLPATTERNDLG_H__0D46AF5B_E8A3_4D87_A2BC_01A8B8D165AE__INCLUDED_)
#define AFX_FILLPATTERNDLG_H__0D46AF5B_E8A3_4D87_A2BC_01A8B8D165AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FillPatternDlg.h : header file
#include "fillgradientdlg.h"
#include "HatchWellBtn.h"
/////////////////////////////////////////////////////////////////////////////
// CFillPatternDlg dialog
class SVIZDLLEXPORT CFillPatternDlg : public CPropertyPage
{
// Construction
public:
	CFillPatternDlg(CWnd* pParent = NULL);   // standard constructor
	DECLARE_DYNAMIC(CFillPatternDlg);
// Dialog Data
	//{{AFX_DATA(CFillPatternDlg)
	enum { IDD = IDD_SVIZ_FILL_PATTERN };
	CSVizHatchWell	m_hatchbtn;
	CSampleButton	m_sample;
	CColourPicker	m_backColorCtrl;
	CColourPicker	m_foreColorCtrl;
	//}}AFX_DATA

	void			DrawSample		();
	void			SetValue		();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillPatternDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFillPatternDlg)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
    afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
    afx_msg LONG OnSelHatchEndOK(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////



#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
