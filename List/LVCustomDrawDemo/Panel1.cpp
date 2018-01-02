// Panel1.cpp : implementation file
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "Panel1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanel1 property page

IMPLEMENT_DYNCREATE(CPanel1, CPropertyPage)

CPanel1::CPanel1() : CPropertyPage(CPanel1::IDD)
{
	//{{AFX_DATA_INIT(CPanel1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPanel1::~CPanel1()
{
}

void CPanel1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanel1)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanel1, CPropertyPage)
	//{{AFX_MSG_MAP(CPanel1)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanel1 message handlers

BOOL CPanel1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    FillListCtrl ( m_list );
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPanel1::OnSetActive() 
{
CPropertySheet* pSheet = static_cast<CPropertySheet*>( GetParent() );

    pSheet->SetWizardButtons ( PSWIZB_NEXT );
    
	return CPropertyPage::OnSetActive();
}

void CPanel1::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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
        // This is the prepaint stage for an item. Here's where we set the
        // item's text color. Our return value will tell Windows to draw the
        // item itself, but it will use the new color we set here.
        // We'll cycle the colors through red, green, and light blue.
        COLORREF crText;

        if ( (pLVCD->nmcd.dwItemSpec % 3) == 0 )
            crText = RGB(255,0,0);
        else if ( (pLVCD->nmcd.dwItemSpec % 3) == 1 )
            crText = RGB(0,255,0);
        else
            crText = RGB(128,128,255);

        // Store the color back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrText = crText;

        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
        }
}
