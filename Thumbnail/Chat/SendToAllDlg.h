#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"
// CSendToAllDlg 对话框

class CSendToAllDlg : public CDialog
{
	DECLARE_DYNAMIC(CSendToAllDlg)

public:
	CSendToAllDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendToAllDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_str;
	CWinXPButtonST m_bt1;
	CWinXPButtonST m_bt2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
