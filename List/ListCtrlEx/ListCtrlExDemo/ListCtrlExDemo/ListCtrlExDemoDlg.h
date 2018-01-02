// ListCtrlExDemoDlg.h : header file
//

#pragma once
#include "afxcmn.h"

#include "ListCtrlEx.h"


// CListCtrlExDemoDlg dialog
class CListCtrlExDemoDlg : public CDialog
{
// Construction
public:
	CListCtrlExDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LISTCTRLEXDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	ListCtrlEx::CListCtrlEx m_list;
};
