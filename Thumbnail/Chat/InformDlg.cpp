// InformDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "InformDlg.h"


// CInformDlg 对话框

IMPLEMENT_DYNAMIC(CInformDlg, CDialog)
CInformDlg::CInformDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInformDlg::IDD, pParent)
{
}

CInformDlg::~CInformDlg()
{
}

void CInformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
}


BEGIN_MESSAGE_MAP(CInformDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CInformDlg 消息处理程序

HBRUSH CInformDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
	return br;
	return hbr;
}

BOOL CInformDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

void CInformDlg::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(nIDEvent);
	CDialog::OnTimer(nIDEvent);
	CDialog::OnCancel();
}

void CInformDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	 SetTimer(0,2000,NULL);

	// TODO: 在此添加消息处理程序代码
}
