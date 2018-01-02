// ChoiceKindDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Chat.h"
#include "ChoiceKindDlg.h"


// CChoiceKindDlg 对话框

IMPLEMENT_DYNAMIC(CChoiceKindDlg, CDialog)
CChoiceKindDlg::CChoiceKindDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChoiceKindDlg::IDD, pParent)
{
	machine = false;
}

CChoiceKindDlg::~CChoiceKindDlg()
{
}

void CChoiceKindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, m_ratio);
	DDX_Control(pDX, IDOK, bt1);
}


BEGIN_MESSAGE_MAP(CChoiceKindDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChoiceKindDlg 消息处理程序

void CChoiceKindDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == BST_CHECKED )
	{
		machine = true;
	}
	OnOK();
}

BOOL CChoiceKindDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常：OCX 属性页应返回 FALSE
}

HBRUSH CChoiceKindDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	pDC->SetBkMode(TRANSPARENT);
	hbr = ::CreateSolidBrush(RGB(128,128,200));
	
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
