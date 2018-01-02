#pragma once
#include "afxwin.h"
#include "IconComboBox.h"
#include "afxcmn.h"
#include "WinXPButtonST.h"


// CUserInfoDlg 对话框

class CUserInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUserInfoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_name;
	CString ip;
	CIPAddressCtrl m_ipctrl;
	CImageList m_imagelist;
	int m_curentimage;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CWinXPButtonST m_button1;
	CWinXPButtonST m_button2;
	CComboBoxEx m_comboxex;
};
