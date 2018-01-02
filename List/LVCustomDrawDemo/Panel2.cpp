// Panel2.cpp : implementation file
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "Panel2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanel2 property page

IMPLEMENT_DYNCREATE(CPanel2, CPropertyPage)

CPanel2::CPanel2() : CPropertyPage(CPanel2::IDD)
{
	//{{AFX_DATA_INIT(CPanel2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPanel2::~CPanel2()
{
}

void CPanel2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanel2)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanel2, CPropertyPage)
	//{{AFX_MSG_MAP(CPanel2)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanel2 message handlers

BOOL CPanel2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    ListView_SetExtendedListViewStyleEx ( 
        m_list.GetSafeHwnd(), 
        LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT );

    FillListCtrl ( m_list );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPanel2::OnSetActive() 
{
CPropertySheet* pSheet = static_cast<CPropertySheet*>( GetParent() );

    pSheet->SetWizardButtons ( PSWIZB_BACK | PSWIZB_NEXT );
    
	return CPropertyPage::OnSetActive();
}

void CPanel2::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

    // Take the default processing unless we set this to something else below.
    *pResult = 0;

    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        *pResult = CDRF_NOTIFYITEMDRAW;
        }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        // This is the notification message for an item.  We'll request
        // notifications before each subitem's prepaint stage.

        *pResult = CDRF_NOTIFYSUBITEMDRAW;
        }
    else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
        {
        // This is the prepaint stage for a subitem. Here's where we set the
        // item's text and background colors. Our return value will tell 
        // Windows to draw the subitem itself, but it will use the new colors
        // we set here.
        // The text color will cycle through red, green, and light blue.
        // The background color will be light blue for column 0, red for
        // column 1, and black for column 2.
    
        COLORREF crText, crBkgnd;
        
        if ( 0 == pLVCD->iSubItem )
            {
            crText = RGB(255,0,0);
            crBkgnd = RGB(128,128,255);
            }
        else if ( 1 == pLVCD->iSubItem )
            {
            crText = RGB(0,255,0);
            crBkgnd = RGB(255,0,0);
            }
        else
            {
            crText = RGB(128,128,255);
            crBkgnd = RGB(0,0,0);
            }

        // Store the colors back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrText = crText;
        pLVCD->clrTextBk = crBkgnd;

        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
        }
}
