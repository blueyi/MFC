#if !defined(AFX_WAITINGEXPORTIMAGESDLG_H__5292F6EA_1BBE_4B0C_9F4E_E37BEBD759A9__INCLUDED_)
#define AFX_WAITINGEXPORTIMAGESDLG_H__5292F6EA_1BBE_4B0C_9F4E_E37BEBD759A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitingExportImagesDlg.h : header file
//
#include"resource.h"
#include "DynLine.h"
/////////////////////////////////////////////////////////////////////////////
// CWaitingExportImagesDlg dialog

class CWaitingExportImagesDlg : public CDialog
{
// Construction
public:
	CDynLine	m_dynline;
public:
	BOOL OnCloseWaitingDlg();
	CWaitingExportImagesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaitingExportImagesDlg)
	enum { IDD = IDD_DIALOG_WAITING_EXPORT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitingExportImagesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaitingExportImagesDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITINGEXPORTIMAGESDLG_H__5292F6EA_1BBE_4B0C_9F4E_E37BEBD759A9__INCLUDED_)
