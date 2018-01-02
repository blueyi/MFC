// SysImageListDlg.h : header file
//

#if !defined(AFX_SYSIMAGELISTDLG_H__A2EB9866_43FA_11D2_8087_00805F7DB281__INCLUDED_)
#define AFX_SYSIMAGELISTDLG_H__A2EB9866_43FA_11D2_8087_00805F7DB281__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SystemImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CSysImageListDlg dialog

class CSysImageListDlg : public CDialog
{
// Construction
public:
	CSysImageListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSysImageListDlg)
	enum { IDD = IDD_SYSIMAGELIST_DIALOG };
	CTreeCtrl	m_Tree;
	CListCtrl	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysImageListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSystemImageList    m_ImgList;
    
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSysImageListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSIMAGELISTDLG_H__A2EB9866_43FA_11D2_8087_00805F7DB281__INCLUDED_)
