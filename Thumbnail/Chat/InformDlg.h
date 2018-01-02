#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"

// CInformDlg 对话框

class CInformDlg : public CDialog
{
	DECLARE_DYNAMIC(CInformDlg)

public:
	CInformDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInformDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
public:
	CString info;

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
