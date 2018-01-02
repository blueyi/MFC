// TabDialog2.cpp : implementation file
//

#include "stdafx.h"
#include "XPTabApp.h"
#include "TabDialog2.h"


// CTabDialog2 dialog

IMPLEMENT_DYNAMIC(CTabDialog2, CDialog)

CTabDialog2::CTabDialog2(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDialog2::IDD, pParent)
{

}

CTabDialog2::~CTabDialog2()
{
}

void CTabDialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabDialog2, CDialog)
END_MESSAGE_MAP()


// CTabDialog2 message handlers
