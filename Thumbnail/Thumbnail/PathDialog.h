//////////////////////////////////////////////////////////////////////////
//PathDialog.h file
//
//Written by Nguyen Tan Hung <tanhung@yahoo.com>
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PATHDIALOG_H__0F70BC86_11DB_11D4_B012_0000E8DD8DAA__INCLUDED_)
#define AFX_PATHDIALOG_H__0F70BC86_11DB_11D4_B012_0000E8DD8DAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathDialog.h : header file
//
#include "shlobj.h"


// CPathDialogSub - intercepts messages from child controls
class CPathDialog : public CWnd
{
public:
	CPathDialog( LPCTSTR lpszCaption=NULL,
				 LPCTSTR lpszTitle=NULL,
				 LPCTSTR lpszInitialPath=NULL, 
				 CWnd* pParent = NULL );

	CString GetPathName();
	virtual int DoModal();

private:
	static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam, LPARAM pData);

	TCHAR	m_lpszInitialPath[MAX_PATH];
	TCHAR	m_szPathName[MAX_PATH];
	TCHAR	m_lpszTitle[256];
	TCHAR	m_lpszCaption[256];

	BROWSEINFO	m_bi;

	CWnd*	m_pParentWnd;
	BOOL	m_bParentDisabled;
	BOOL	m_bGetSuccess;

protected:
    afx_msg void OnOK();              // OK button clicked
	afx_msg void OnChangeEditPath();
    DECLARE_MESSAGE_MAP()
private:
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHDIALOG_H__0F70BC86_11DB_11D4_B012_0000E8DD8DAA__INCLUDED_)
