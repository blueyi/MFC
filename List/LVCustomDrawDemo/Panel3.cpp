// Panel3.cpp : implementation file
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "Panel3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanel3 property page

IMPLEMENT_DYNCREATE(CPanel3, CPropertyPage)

CPanel3::CPanel3() : CPropertyPage(CPanel3::IDD)
{
	//{{AFX_DATA_INIT(CPanel3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPanel3::~CPanel3()
{
}

void CPanel3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanel3)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanel3, CPropertyPage)
	//{{AFX_MSG_MAP(CPanel3)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanel3 message handlers

BOOL CPanel3::OnInitDialog() 
{
CWinApp* pApp = AfxGetApp();
HICON    hStan, hKyle, hCartman, hKenny;

	CPropertyPage::OnInitDialog();
	
	// Set up the image list.
	
    m_imglist.Create ( 48, 48, ILC_COLOR16 | ILC_MASK, 4, 1 );

    hStan = reinterpret_cast<HICON>(
                ::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_STAN),
                              IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR ));
    hKyle = reinterpret_cast<HICON>(
                ::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_KYLE),
                              IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR ));
    hCartman = reinterpret_cast<HICON>(
                ::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_CARTMAN),
                              IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR ));
    hKenny = reinterpret_cast<HICON>(
                ::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_KENNY),
                              IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR ));

    m_imglist.Add ( hStan );
    m_imglist.Add ( hKyle );
    m_imglist.Add ( hCartman );
    m_imglist.Add ( hKenny );

    m_list.SetImageList ( &m_imglist, LVSIL_SMALL );
    m_list.InsertColumn ( 0, _T("South Park"), LVCFMT_LEFT, 0, 0 );

    // And set up the list items.

    m_list.InsertItem ( 0, _T("Stan Marsh"), 0 );
    m_list.InsertItem ( 1, _T("Kyle Brovlofsky"), 1 );
    m_list.InsertItem ( 2, _T("Eric Cartman"), 2 );
    m_list.InsertItem ( 3, _T("Kenny McCormick"), 3 );

    m_list.SetColumnWidth ( 0, LVSCW_AUTOSIZE );

    m_list.SetExtendedStyle ( LVS_EX_FULLROWSELECT );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPanel3::OnSetActive() 
{
CPropertySheet* pSheet = static_cast<CPropertySheet*>( GetParent() );

    pSheet->SetWizardButtons ( PSWIZB_BACK | PSWIZB_NEXT );
    
	return CPropertyPage::OnSetActive();
}

void CPanel3::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
    
    *pResult = 0;

    // If this is the beginning of the control's paint cycle, request
    // notifications for each item.

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        *pResult = CDRF_NOTIFYITEMDRAW;
        }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        // This is the pre-paint stage for an item.  We need to make another
        // request to be notified during the post-paint stage.

        *pResult = CDRF_NOTIFYPOSTPAINT;
        }
    else if ( CDDS_ITEMPOSTPAINT == pLVCD->nmcd.dwDrawStage )
        {
        // If this item is selected, re-draw the icon in its normal
        // color (not blended with the highlight color).
        LVITEM rItem;
        int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

        // Get the image index and state of this item.  Note that we need to
        // check the selected state manually.  The docs _say_ that the
        // item's state is in pLVCD->nmcd.uItemState, but during my testing
        // it was always equal to 0x0201, which doesn't make sense, since
        // the max CDIS_ constant in commctrl.h is 0x0100.

        ZeroMemory ( &rItem, sizeof(LVITEM) );
        rItem.mask  = LVIF_IMAGE | LVIF_STATE;
        rItem.iItem = nItem;
        rItem.stateMask = LVIS_SELECTED;
        m_list.GetItem ( &rItem );

        // If this item is selected, redraw the icon with its normal colors.

        if ( rItem.state & LVIS_SELECTED )
            {
            CDC*  pDC = CDC::FromHandle ( pLVCD->nmcd.hdc );
            CRect rcIcon;

            // Get the rect that holds the item's icon.
            m_list.GetItemRect ( nItem, &rcIcon, LVIR_ICON );

            // Draw the icon.
            m_imglist.Draw ( pDC, rItem.iImage, rcIcon.TopLeft(),
                             ILD_TRANSPARENT );

            *pResult = CDRF_SKIPDEFAULT;
            }
        }
}
