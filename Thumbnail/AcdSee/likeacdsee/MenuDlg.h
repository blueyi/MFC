#if !defined(AFX_MENUDLG_H__DC102E86_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
#define AFX_MENUDLG_H__DC102E86_D246_11D6_AFCA_001088A02FAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuDlg dialog

class CMenuDlg : public CDialog
{
// Construction
public:
	CMenuDlg(CWnd* pParent = NULL);   // standard constructor
    
// Dialog Data
	//{{AFX_DATA(CMenuDlg)
	enum { IDD = IDD_MENU_DIALOG };
	//}}AFX_DATA
protected:
    

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
     
	// Generated message map functions
	//{{AFX_MSG(CMenuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUDLG_H__DC102E86_D246_11D6_AFCA_001088A02FAC__INCLUDED_)
