// Wizard.cpp : implementation file
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "Wizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWizard

IMPLEMENT_DYNAMIC(CWizard, CPropertySheet)

CWizard::CWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CWizard::CWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CWizard::~CWizard()
{
}


BEGIN_MESSAGE_MAP(CWizard, CPropertySheet)
	//{{AFX_MSG_MAP(CWizard)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizard message handlers

int CWizard::DoModal() 
{
    AddPage ( &m_panel1 );
    AddPage ( &m_panel2 );
    AddPage ( &m_panel3 );
    AddPage ( &m_panel4 );
    
    m_panel1.m_psp.dwFlags &= ~PSP_HASHELP;
    m_panel2.m_psp.dwFlags &= ~PSP_HASHELP;
    m_panel3.m_psp.dwFlags &= ~PSP_HASHELP;
    m_panel4.m_psp.dwFlags &= ~PSP_HASHELP;

    m_psh.dwFlags &= ~PSH_HASHELP;
    m_psh.dwFlags |= PSH_WIZARD;

	return CPropertySheet::DoModal();
}
