/////////////////////////////////////////////////////////////////////////////
// InfoDlg.h : header file
//
// Operating system checking function
// All rights reserved.
//
// Written by Naveen Kohli (naveen@a3ds.com)
// Version 1.0
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc. to
//    naveen@a3ds.com
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFODLG_H__B2D9C740_3822_11D2_8B51_000000000000__INCLUDED_)
#define AFX_INFODLG_H__B2D9C740_3822_11D2_8B51_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// InfoDlg dialog

class InfoDlg : public CDialog
{
// Construction
public:
	InfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InfoDlg)
	enum { IDD = IDD_INFO_DIALOG };

	CString m_stInfo;
	CString m_stMinorVer;
	CString m_stServPack;
	CString m_stBuildNumber;
	
	CStatic m_InfoStatic;
	CStatic m_MinorVerStatic;
	CStatic m_ServPackStatic;
	CStatic m_BuildNoStatic;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	void CheckOSVersion ();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InfoDlg)
	virtual BOOL OnInitDialog();
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__B2D9C740_3822_11D2_8B51_000000000000__INCLUDED_)
