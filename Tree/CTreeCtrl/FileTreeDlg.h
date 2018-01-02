// FileTreeDlg.h : header file
//

#if !defined(AFX_FILETREEDLG_H__81931B79_DECC_47E1_8F02_B92E781BB573__INCLUDED_)
#define AFX_FILETREEDLG_H__81931B79_DECC_47E1_8F02_B92E781BB573__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileTreeDlg dialog

class CFileTreeDlg : public CDialog
{
// Construction
public:
	CFileTreeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileTreeDlg)
	enum { IDD = IDD_FILETREE_DIALOG };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileTreeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileTreeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

	void AddFile( CString StrPath, HTREEITEM faItem );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILETREEDLG_H__81931B79_DECC_47E1_8F02_B92E781BB573__INCLUDED_)
