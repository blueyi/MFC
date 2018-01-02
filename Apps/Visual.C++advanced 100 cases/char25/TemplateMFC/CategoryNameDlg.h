#if !defined(AFX_CATEGORYNAMEDLG_H__E3EC3896_684E_11D2_BFF9_0020186676FB__INCLUDED_)
#define AFX_CATEGORYNAMEDLG_H__E3EC3896_684E_11D2_BFF9_0020186676FB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CategoryNameDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategoryNameDlg dialog

class CCategoryNameDlg : public CDialog
{
// Construction
public:
	CString GetName();
	CCategoryNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCategoryNameDlg)
	enum { IDD = IDD_NEW_CATEGORY_DIALOG };
	CString	m_categoryName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategoryNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCategoryNameDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATEGORYNAMEDLG_H__E3EC3896_684E_11D2_BFF9_0020186676FB__INCLUDED_)
