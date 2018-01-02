// PPOne.cpp : implementation file
//

#include "stdafx.h"
#include "tabctrl.h"
#include "PPOne.h"
#include ".\ppone.h"


// CPPOne dialog

IMPLEMENT_DYNAMIC(CPPOne, CPropertyPage)
CPPOne::CPPOne()
	: CPropertyPage(CPPOne::IDD)
{
}

CPPOne::~CPPOne()
{
}

void CPPOne::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPPOne, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_MSG, OnBnClickedButtonMsg)
END_MESSAGE_MAP()


// CPPOne message handlers

void CPPOne::OnBnClickedButtonMsg()
{
	// TODO: Add your control notification handler code here
	MessageBox("May this tab control help you! - venura","Message",MB_OK|MB_ICONEXCLAMATION);
}
