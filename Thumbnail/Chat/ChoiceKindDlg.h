#pragma once
#include "afxwin.h"
#include "WinXPButtonST.h"

// CChoiceKindDlg 对话框

class CChoiceKindDlg : public CDialog
{
	DECLARE_DYNAMIC(CChoiceKindDlg)

public:
	CChoiceKindDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChoiceKindDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool machine;
	afx_msg void OnBnClickedOk();
	CWinXPButtonST m_ratio;
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST bt1;
};
