#if !defined(AFX_EXPORTSETTINGSDLG_H__0AED4D8B_8465_4B31_931C_2B2987E6A981__INCLUDED_)
#define AFX_EXPORTSETTINGSDLG_H__0AED4D8B_8465_4B31_931C_2B2987E6A981__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"resource.h"
// ExportSettingsDlg.h : header file
//
#include "DynLine.h"


/////////////////////////////////////////////////////////////////////////////
// CExportSettingsDlg dialog

class CExportSettingsDlg : public CDialog
{
// Construction
public:
	BOOL m_bPrintMethod;
public:
	CExportSettingsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExportSettingsDlg)
	enum { IDD = IDD_DIALOG_EXPORT_SETTING_DLG };
	CString	m_strFileType;
	CString	m_strFilePathName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExportSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExportSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton1();
	afx_msg void OnRadioDefaultSave();
	afx_msg void OnRadioSaveByFolder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPORTSETTINGSDLG_H__0AED4D8B_8465_4B31_931C_2B2987E6A981__INCLUDED_)
