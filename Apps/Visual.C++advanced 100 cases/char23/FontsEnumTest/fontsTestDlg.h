// fontsTestDlg.h : header file
//

#if !defined(AFX_FONTSTESTDLG_H__8D233C19_8B2A_11D1_92BB_006097AEFD47__INCLUDED_)
#define AFX_FONTSTESTDLG_H__8D233C19_8B2A_11D1_92BB_006097AEFD47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "WizFontsEnumerator.h"
#include "WizFontNamesComboBox.h"
#include "WizFontScriptsComboBox.h"
#include "WizFontSizesComboBox.h"
#include "WizFontExampleStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CFontsTestDlg dialog

class CFontsTestDlg : public CDialog
{
// Construction
public:
	CFontsTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFontsTestDlg)
	enum { IDD = IDD_FONTSTEST_DIALOG };
	CWizFontExampleStatic	m_SampleBox;
	CButton					m_Underline;
	CButton					m_Italic;
	CWizFontSizesComboBox	m_SizeCombo;
	CWizFontScriptsComboBox	m_ScriptCombo;
	CButton					m_bold;
	CWizFontNamesComboBox	m_FontNamesCombo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontsTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON				m_hIcon;
	CWizFontsEnumerator	m_Fonts;

	// Generated message map functions
	//{{AFX_MSG(CFontsTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBoldCheck();
	afx_msg void OnSelchangeComboSize();
	afx_msg void OnSelchangeComboScript();
	afx_msg void OnItalicCheck();
	afx_msg void OnUnderlineCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void	FontChanged();
	void	Update4NewFontName();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTSTESTDLG_H__8D233C19_8B2A_11D1_92BB_006097AEFD47__INCLUDED_)
