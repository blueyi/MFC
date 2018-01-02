// Panel4.cpp : implementation file
//

#include "stdafx.h"
#include "LVCustomDraw.h"
#include "Panel4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanel4 property page

IMPLEMENT_DYNCREATE(CPanel4, CPropertyPage)

CPanel4::CPanel4() : CPropertyPage(CPanel4::IDD)
{
	//{{AFX_DATA_INIT(CPanel4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPanel4::~CPanel4()
{
}

void CPanel4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPanel4)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPanel4, CPropertyPage)
	//{{AFX_MSG_MAP(CPanel4)
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnCustomdrawList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanel4 message handlers

BOOL CPanel4::OnSetActive() 
{
CPropertySheet* pSheet = static_cast<CPropertySheet*>( GetParent() );

    pSheet->SetWizardButtons ( PSWIZB_BACK | PSWIZB_FINISH );
    
	return CPropertyPage::OnSetActive();
}

BOOL CPanel4::OnInitDialog() 
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
    m_list.InsertColumn ( 0, _T(""), LVCFMT_LEFT, 0, 0 );

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

void CPanel4::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
    
    *pResult = 0;

    // Request item-specific notifications if this is the
    // beginning of the paint cycle.

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        *pResult = CDRF_NOTIFYITEMDRAW;
        }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        // This is the beginning of an item's paint cycle.
        LVITEM   rItem;
        int      nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );
        CDC*     pDC   = CDC::FromHandle ( pLVCD->nmcd.hdc );
        COLORREF crBkgnd;
        BOOL     bListHasFocus;
        CRect    rcItem;
        CRect    rcText;
        CString  sText;
        UINT     uFormat;
                        
        bListHasFocus = ( m_list.GetSafeHwnd() == ::GetFocus() );
        
        // Get the image index and selected/focused state of the
        // item being drawn.
        ZeroMemory ( &rItem, sizeof(LVITEM) );
        rItem.mask  = LVIF_IMAGE | LVIF_STATE;
        rItem.iItem = nItem;
        rItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
        m_list.GetItem ( &rItem );

        // Get the rect that holds the item's icon.
        m_list.GetItemRect ( nItem, &rcItem, LVIR_ICON );

        // Draw the icon.
        uFormat = ILD_TRANSPARENT;

        if ( ( rItem.state & LVIS_SELECTED ) && bListHasFocus )
            uFormat |= ILD_FOCUS;

        m_imglist.Draw ( pDC, rItem.iImage, rcItem.TopLeft(), uFormat );


        // Get the rect that bounds the text label.
        m_list.GetItemRect ( nItem, rcItem, LVIR_LABEL );


        // Draw the background of the list item.  Colors are selected 
        // according to the item's state.

        if ( rItem.state & LVIS_SELECTED )
            {
            if ( bListHasFocus )
                {
                crBkgnd = GetSysColor ( COLOR_HIGHLIGHT );
                pDC->SetTextColor ( GetSysColor ( COLOR_HIGHLIGHTTEXT ));
                }
            else
                {
                crBkgnd = GetSysColor ( COLOR_BTNFACE );
                pDC->SetTextColor ( GetSysColor ( COLOR_BTNTEXT ));
                }
            }
        else
            {
            crBkgnd = GetSysColor ( COLOR_WINDOW );
            pDC->SetTextColor ( GetSysColor ( COLOR_BTNTEXT ));
            }

        // Draw the background & prep the DC for the text drawing.  Note
        // that the entire item RECT is filled in, so this emulates the full-
        // row selection style of normal lists.
        pDC->FillSolidRect ( rcItem, crBkgnd );
        pDC->SetBkMode ( TRANSPARENT );


        // Tweak the rect a bit for nicer-looking text alignment.
        rcText = rcItem;
        rcText.left += 3;
        rcText.top++;

        // Draw the text.
        sText = m_list.GetItemText ( nItem, 0 );

        pDC->DrawText ( sText, rcText, DT_VCENTER | DT_SINGLELINE );
        

        // Draw a focus rect around the item if necessary.
        if ( bListHasFocus && ( rItem.state & LVIS_FOCUSED ))
            {
            pDC->DrawFocusRect ( rcItem );
            }

        *pResult = CDRF_SKIPDEFAULT;    // We've painted everything.
        }
}
