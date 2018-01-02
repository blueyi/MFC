//////////////////////////////////////////////////////////////////////////////
//类名：CFireCtrlDlg
//功能：火焰效果示例实现对话框
//作者：徐景周(jingzhou_xu@163.net)
//组织：未来工作室(Future Studio)
//日期：2001.12.1
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_)
#define AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBButton.h"				//加入位图按钮类
#include "HyperLink.h"				//加入超链接类
#include "PictureEx.h"				//加入GIF动态图像显示
#include "FireWnd.h"				//加入火焰效果控件类
/////////////////////////////////////////////////////////////////////////////
// CFireCtrlDlg dialog

class CFireCtrlDlg : public CDialog
{
// Construction
public:
	CFireCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFireCtrlDlg)
	enum { IDD = IDD_FIRECTRL_DIALOG };
	CWBButton	m_About;			//位图按钮
	CWBButton	m_OK;				//位图按钮
	CFireWnd	m_FireCtrl;         //火焰效果控件 
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFireCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRECTRLDLG_H__3466C315_3515_42FC_9080_F4D78A4E0338__INCLUDED_)
