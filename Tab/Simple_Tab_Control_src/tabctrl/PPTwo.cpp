// PPTwo.cpp : implementation file
//

#include "stdafx.h"
#include "tabctrl.h"
#include "PPTwo.h"
#include ".\pptwo.h"


// CPPTwo dialog

IMPLEMENT_DYNAMIC(CPPTwo, CPropertyPage)
CPPTwo::CPPTwo()
	: CPropertyPage(CPPTwo::IDD)
	, m_strEDITName(_T(""))
{
}

CPPTwo::~CPPTwo()
{
}

void CPPTwo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strEDITName);
}


BEGIN_MESSAGE_MAP(CPPTwo, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CPPTwo message handlers

void CPPTwo::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString strMessage;
	strMessage = "Welcome " + m_strEDITName;
	MessageBox(strMessage,"Message",MB_OK|MB_ICONEXCLAMATION);
	UpdateData(false);
}
