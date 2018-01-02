// TabDialog1.cpp : implementation file
//

#include "stdafx.h"
#include "XPTabApp.h"
#include "TabDialog1.h"
#include "XPTabDlg.h"

// CTabDialog1 dialog

IMPLEMENT_DYNAMIC(CTabDialog1, CDialog)

CTabDialog1::CTabDialog1(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDialog1::IDD, pParent)
{

}

CTabDialog1::~CTabDialog1()
{
}

void CTabDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabDialog1, CDialog)
END_MESSAGE_MAP()


// CTabDialog1 message handlers

BOOL CTabDialog1::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    //CXPTabDlg *pParent;
    //CRect rcDlg, rcList;

    ////resize list
    //pParent=(CXPTabDlg *)GetParent();
    //if(pParent != NULL)
    //{
    //    //size to fit to tab control
    //    pParent->m_tab.GetWindowRect(&rcDlg);
    //    GetDlgItem(IDOK)->GetWindowRect(&rcList);
    //    rcList.SetRect(0, 0, rcDlg.Width(), rcList.Height());
    //    GetDlgItem(IDOK)->MoveWindow(&rcList);
    //}

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}
