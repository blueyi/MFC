#if !defined(AFX_PROGRESSANDTIPDLG_H__6837F951_93A0_485F_A657_2ADE4E80B747__INCLUDED_)
#define AFX_PROGRESSANDTIPDLG_H__6837F951_93A0_485F_A657_2ADE4E80B747__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressAndTipDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CProgressAndTipDlg dialog

class CProgressAndTipDlg : public CDialog
{
	// Construction
public:
	int  SetStep(int nStep);
    
    int  StepIt();
	void PumpMessages();
	CProgressAndTipDlg(CWnd* pParent = NULL);   // standard constructor
	
	
	// Dialog Data
	//{{AFX_DATA(CProgressAndTipDlg)
	enum { IDD = IDD_DIALOG_PRO_TIP };
	CProgressCtrl	m_sProgressCtrl;
	CStatic	m_sStatic_Ctrl;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressAndTipDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CProgressAndTipDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSANDTIPDLG_H__6837F951_93A0_485F_A657_2ADE4E80B747__INCLUDED_)
