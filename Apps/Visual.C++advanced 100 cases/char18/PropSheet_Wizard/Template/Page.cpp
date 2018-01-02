// $$PAGE_FILE$$.cpp : implementation file
//

#include "stdafx.h"
#include "$$Root$$.h"
#include "$$PAGE_FILE$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$PAGE_CLASS$$ property page

IMPLEMENT_DYNCREATE($$PAGE_CLASS$$, CPropertyPage)

$$PAGE_CLASS$$::$$PAGE_CLASS$$() : CPropertyPage($$PAGE_CLASS$$::IDD)
{
	//{{AFX_DATA_INIT($$PAGE_CLASS$$)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

$$PAGE_CLASS$$::~$$PAGE_CLASS$$()
{
}

void $$PAGE_CLASS$$::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP($$PAGE_CLASS$$)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP($$PAGE_CLASS$$, CPropertyPage)
	//{{AFX_MSG_MAP($$PAGE_CLASS$$)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$PAGE_CLASS$$ message handlers

$$IF(TOOLTIPS)
BOOL $$PAGE_CLASS$$::PreTranslateMessage (MSG* pMsg)
{
	// Let the ToolTip process this message.
	m_tooltip.RelayEvent(pMsg);

	return CPropertyPage::PreTranslateMessage(pMsg);
}

BOOL $$PAGE_CLASS$$::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Create the ToolTip control.
	m_tooltip.Create (this);
	m_tooltip.Activate (TRUE);

	// TODO: Use one of the following forms to add controls:
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), <string-table-id>);
	// m_tooltip.AddTool (GetDlgItem (IDC_<name>), _T ("<text>"));

	return TRUE;
}
$$ENDIF	//TOOLTIPS
