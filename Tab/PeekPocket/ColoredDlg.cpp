// ColoredDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColoredDlg.h"

// CColoredDlg dialog

IMPLEMENT_DYNAMIC(CColoredDlg, CDialog)

CColoredDlg::CColoredDlg(CWnd* pParent /*=NULL*/)
//	: CDialog(CColoredDlg::IDD, pParent)
{
	//default brush
	m_brBkg.CreateSolidBrush(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
}

CColoredDlg::CColoredDlg(UINT nDialogID, CWnd* pParent /* = NULL */)
{
	m_pParentWnd = pParent;
	m_lpszTemplateName = MAKEINTRESOURCE(nDialogID);
	m_nIDHelp = nDialogID;
	//default brush
	m_brBkg.CreateSolidBrush(RGB_AVERAGE(GetSysColor(COLOR_ACTIVECAPTION), RGB(255, 255, 255)));
}

CColoredDlg::~CColoredDlg()
{
}

BEGIN_MESSAGE_MAP(CColoredDlg, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CColoredDlg message handlers
//////////////////////////////////////////////////////////////////////////
HBRUSH CColoredDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//we can set up the control's painting DC here.
	pDC->SetBkColor(m_crBkg);
	pDC->SetTextColor(m_crFrg);
	pDC->SetBkMode(OPAQUE);
	//and return a background brush
	return m_brBkg;
}

//////////////////////////////////////////////////////////////////////////
void CColoredDlg::SetBkgColor(COLORREF crBkg)
{
	m_crBkg=crBkg;
	//re-create bkg brush
	m_brBkg.DeleteObject();
	m_brBkg.CreateSolidBrush(crBkg);
}

//////////////////////////////////////////////////////////////////////////
void CColoredDlg::SetFrgColor(COLORREF crFrg)
{
	m_crFrg=crFrg;
}
