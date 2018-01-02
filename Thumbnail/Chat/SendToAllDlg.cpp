// SendToAllDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "SendToAllDlg.h"


// CSendToAllDlg 对话框

IMPLEMENT_DYNAMIC(CSendToAllDlg, CDialog)
CSendToAllDlg::CSendToAllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendToAllDlg::IDD, pParent)
	, m_str(_T(""))
{
}

CSendToAllDlg::~CSendToAllDlg()
{
}

void CSendToAllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RICHEDIT21, m_str);
	DDX_Control(pDX, IDOK, m_bt1);
	DDX_Control(pDX, IDCANCEL, m_bt2);
}


BEGIN_MESSAGE_MAP(CSendToAllDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSendToAllDlg 消息处理程序

BOOL CSendToAllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText("消息群发");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

HBRUSH CSendToAllDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	 pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor != CTLCOLOR_LISTBOX &&  nCtlColor !=  CTLCOLOR_EDIT)
	{
		HBRUSH br=::CreateSolidBrush(RGB(128,128,200));
		return br;
	}

	return hbr;
}
