#if !defined(AFX_FILESTATUSDLG_H__37D4C0C4_CEE9_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_FILESTATUSDLG_H__37D4C0C4_CEE9_11D6_AFCA_001088A02FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileStatusDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileStatusDlg dialog

class CFileStatusDlg : public CDialog
{
// Construction
public:
	CFileStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFileStatusDlg)
	enum { IDD = IDD_FILESTATUSDIALOG };
	CString	m_strfilepath;
	CString	m_strfilesize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileStatusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileStatusDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESTATUSDLG_H__37D4C0C4_CEE9_11D6_AFCA_001088A02FAC__INCLUDED_)
