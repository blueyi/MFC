// NewButton.cpp : implementation file
//

#include "stdafx.h"
#include "ThumbNail.h"
#include "NewButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewButton

CNewButton::CNewButton()
{
}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	//{{AFX_MSG_MAP(CNewButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewButton message handlers

BOOL CNewButton::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CButton::PreTranslateMessage(pMsg);
}
