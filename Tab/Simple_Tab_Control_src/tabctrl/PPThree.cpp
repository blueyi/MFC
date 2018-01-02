// PPThree.cpp : implementation file
//

#include "stdafx.h"
#include "tabctrl.h"
#include "PPThree.h"


// CPPThree dialog

IMPLEMENT_DYNAMIC(CPPThree, CPropertyPage)
CPPThree::CPPThree()
	: CPropertyPage(CPPThree::IDD)
{
}

CPPThree::~CPPThree()
{
}

void CPPThree::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPPThree, CPropertyPage)
END_MESSAGE_MAP()


// CPPThree message handlers
