// MainSheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "KeyHook.h"
#include "Property.h"
#include "MainSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainSheet

IMPLEMENT_DYNAMIC(CMainSheet, CPropertySheet)

CMainSheet::CMainSheet(CWnd* pParentWnd)
: CPropertySheet(IDS_PROPSHEET_TITLE, pParentWnd)
{
	m_propDlg = new CPropertyDlg;
	m_aboutDlg = new CPropertyPage(IDD_ABOUT_DIALOG);

	m_psh.dwFlags &= ~(PSH_HASHELP);
	m_propDlg->m_psp.dwFlags &= ~(PSP_HASHELP);
	m_aboutDlg->m_psp.dwFlags &= ~(PSP_HASHELP);

	AddPage(m_propDlg);
	AddPage(m_aboutDlg);
}

CMainSheet::~CMainSheet()
{
	delete m_propDlg;
	delete m_aboutDlg;
}

BEGIN_MESSAGE_MAP(CMainSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMainSheet)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainSheet message handlers

BOOL CMainSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
     LONG style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
     style |= WS_EX_CONTEXTHELP;
     ::SetWindowLong(m_hWnd, GWL_EXSTYLE, style);
	
	return bResult;
}

#include "resource.hm"

BOOL CMainSheet::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	switch(pHelpInfo->iCtrlId)
	{
		case IDC_BITMAP:
		case IDC_STATIC_CLICKIMAGE:
			AfxGetApp()->WinHelp(HIDC_BITMAP, HELP_CONTEXTPOPUP);
			return TRUE;

		case IDC_CHECK_PERSIST:
			AfxGetApp()->WinHelp(HIDC_CHECK_PERSIST, HELP_CONTEXTPOPUP);
			return TRUE;

		case IDC_STATIC_HOTKEY:
		case IDC_HOTKEY:
			AfxGetApp()->WinHelp(HIDC_HOTKEY, HELP_CONTEXTPOPUP);
			return TRUE;

		case IDC_STATIC_ZOOMFACTOR:
		case IDC_FACTOR:
		case IDC_FACTOR_SPIN:
		case IDC_STATIC_FACTORPIXELS:
			AfxGetApp()->WinHelp(HIDC_FACTOR, HELP_CONTEXTPOPUP);
			return TRUE;
		
		case IDC_STATIC_ZOOMAREA:
		case IDC_STATIC_AREAPIXELS:
		case IDC_WIDTH:
		case IDC_WIDTH_SPIN:
			AfxGetApp()->WinHelp(HIDC_WIDTH, HELP_CONTEXTPOPUP);
			return TRUE;

		default:
			AfxGetApp()->WinHelp(HIDC_STATIC, HELP_CONTEXTPOPUP);
			return TRUE;
	}
}
