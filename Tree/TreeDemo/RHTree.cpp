/////////////////////////////////////////////////////////////////////
// CRHTree, 2nd version (Aug 07)
// Written by Paul Roberts, http://www.tlhouse.co.uk
//
// Inspired by Jim Alsup's VividTree article: 
// http://www.codeproject.com/treectrl/VividTree.asp
//
// Use it freely, but please leave this header intact
//

#include "stdafx.h"
#include <windowsx.h>
#include "Resource.h"
#include "RHTree.h"
#include "ResourceUtils.h"
#include ".\rhtree.h"

IMPLEMENT_DYNAMIC(CRHTree, CTreeCtrl)
CRHTree::CRHTree()
{
	m_bThemeInited = FALSE;
	m_hWidgetHlt = NULL;
	m_nHSpacer = 0;
	m_hWidgetExpand = NULL;
	m_hWidgetCollapse = NULL;
	m_hWidgetExpandHot = NULL;
	m_hWidgetCollapseHot = NULL;
	m_crWidgetBack = 0;
}

CRHTree::~CRHTree()
{
	this->DestroyWidgetIcons();
}


BEGIN_MESSAGE_MAP(CRHTree, CTreeCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave )
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()



// CRHTree message handlers


void CRHTree::OnPaint()
{
	CPaintDC	dc(this);		// Device context for painting
	CDC			dcOffscreen;	// Memory base device context for flicker free painting
	CBitmap		bmOffscreen;	// The bitmap we paint into
	CFont*		pFont = NULL;
	CRect		rClient;
	//

	this->GetClientRect( &rClient );
	
	// Create an offscreen dc to paint with (prevents flicker issues)
	dcOffscreen.CreateCompatibleDC( &dc );
    bmOffscreen.CreateCompatibleBitmap( &dc, rClient.Width(), rClient.Height() );
    
    // Let's prepare to return all settings we change
    int nSaveDC = dcOffscreen.SaveDC();
    
    // Select the bitmap into the off-screen DC.
    dcOffscreen.SelectObject( &bmOffscreen );
    
	// Default pFont in the DC is not the pFont used by 
	// the tree control, so grab it and select it in.
	pFont = this->GetFont();
	dcOffscreen.SelectObject( pFont );
	
	// We're going to draw text transparently
	dcOffscreen.SetBkMode( TRANSPARENT );
	
	// Calculate spacers...
	m_nHSpacer = this->CalcHorzSpacer( &dcOffscreen );

	// Draw the background and the items...
	this->DrawBackground( &dcOffscreen, rClient );
	this->DrawItems( &dcOffscreen, rClient );

    // Now Blt the changes to the real device context - this prevents flicker.
    dc.BitBlt( rClient.left, rClient.top, rClient.Width(), rClient.Height(), &dcOffscreen, 0, 0, SRCCOPY);

	// Put things back as they were...
	dcOffscreen.RestoreDC( nSaveDC );
}

void CRHTree::InitTheme()
// Initialise theme support if it hasn't been done already
{
	if ( !m_bThemeInited )
	{
		m_Theme.Init( m_hWnd );
		m_bThemeInited = TRUE;
	}
}

void CRHTree::DrawBackground( CDC* pDC, CRect rClient )
{
	pDC->FillSolidRect( rClient, this->GetPartColor(eItemBack) );
}

void CRHTree::DrawItems( CDC* pDC, CRect rClient )
// Loops through all visible items in the tree and draws them
{
	HTREEITEM	hItem = NULL;
	CRect		rItem;
	//
	
	// Get the current top item, if any...
	hItem = GetFirstVisibleItem();

	// Work through them one at a time...
	while ( hItem )
	{
		// Get the item's text rectangle...
		this->GetItemRect( hItem, rItem, TRUE );
		
		// Compensate for the now shifted buttons...
		this->OffsetTextRect( rItem );
	
		// Draw this item...
		this->DrawItem( pDC, rClient, hItem, rItem );
	
		// On to the next one...
		hItem = this->GetNextVisibleItem( hItem );
	}// end of loop
}

void CRHTree::OffsetTextRect( CRect& rText )
// Depending on the styles that are set, the text rectangle might need
// to have its left edge adjusted, since the underlying control will make
// room for items that are normally on the left (+/- button, checkbox)
{
	CRect		rRoot;
	CRect		rRootText;
	//

	if ( this->GetItemRect(this->GetRootItem(), rRoot, FALSE) && this->GetItemRect(this->GetRootItem(), rRootText, TRUE) )
		rText.left = m_nHSpacer + max(0, rText.left - (rRootText.left - rRoot.left)) - this->GetScrollPos(SB_HORZ);
		
	if ( this->GetImageList(TVSIL_NORMAL) )
		rText.left += ::GetSystemMetrics(SM_CXSMICON) + m_nHSpacer;
}

int CRHTree::CalcHorzSpacer( CDC* pDC )
// There are various situations where we need a little gap horizontally.
// Let's standardize on something that looks right in most (all?) cases.
{
	// Width of a space character works well
	CSize sizeChar = pDC->GetTextExtent( CString(_T(" ")) );
	return sizeChar.cx;
}

COLORREF CRHTree::GetPartColor( TreeColor nClr )
// Override to change any/all part colors
{
	COLORREF	cr = 0;

	switch ( nClr )
	{
		case eGroupText:
			cr = ::GetSysColor( COLOR_WINDOWTEXT );
		break;
		
		case eGroupBack:
			cr = ::GetSysColor( COLOR_WINDOW );
		break;
		
		case eItemText:
			cr = ::GetSysColor( COLOR_WINDOWTEXT );
		break;
		
		case eItemBack:
			cr = ::GetSysColor( COLOR_WINDOW );
		break;
	}
	
	return cr;
}

void CRHTree::DrawItem( CDC* pDC, CRect rClient, HTREEITEM hItem, CRect rItem )
// Draws an individual item in the tree. 
{
	int		nSmallIconWidth = ::GetSystemMetrics(SM_CXSMICON);
	CRect	rDraw;
	CRect	rWidget( 0,0,0,0 );
	CRect	rCheck( 0,0,0,0 );
	CRect	rText( 0,0,0,0 );
	LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 
	int		nState = 0;
	BOOL	bIsGroup = FALSE;
	BOOL	bSelected = FALSE;
	//
	
	// Work out the drawing area...
	rDraw = rClient;
	rDraw.top = rItem.top;
	rDraw.bottom = rItem.bottom;
	
	// Work out the widget drawing area...
	rWidget = rDraw;
	this->GetWidgetHRange( rWidget.left, rWidget.right ); // V2 - use this function
	
	// Work out the checkbox drawing area, if any...
	if ( nStyle & TVS_CHECKBOXES )
	{
		rCheck = rDraw;
		rCheck.right -= rWidget.Width();
		rCheck.left = rCheck.right - nSmallIconWidth;
	}
	
	// Work out the text drawing area...
	rText = rItem;
	rText.right = rClient.right - rWidget.Width() - rCheck.Width() - m_nHSpacer;
	
	// Work out item state...
	nState = this->GetItemState( hItem, TVIF_STATE );
	bIsGroup = this->IsGroup( hItem );
	bSelected = (nState & TVIS_SELECTED) && ((this == GetFocus()) || (nStyle & TVS_SHOWSELALWAYS));
	
	if ( bIsGroup )
	{
		this->DrawGroupWash( pDC, rDraw );
		this->DrawItemImage( pDC, rText, hItem, bSelected );
		this->DrawGroupTitle( pDC, rText, this->GetItemText(hItem) );
		this->DrawWidget( pDC, rWidget, nState & TVIS_EXPANDED, m_hWidgetHlt == hItem );
	}
	else
	{
		this->DrawItemImage( pDC, rText, hItem, bSelected );
		this->DrawItemTitle( pDC, rText, this->GetItemText(hItem) );
	}
		
	// Draw lines if appropriate...
	this->DrawItemLines( pDC, hItem );	
	
	//  Now apply a selection wash, if appropriate
	if ( bSelected )
	{
		//
		// GDI+ lets us easily paint a transparent colored layer over the item
		//

		// Let's have our GDI+ graphics wrapper...
		Gdiplus::Graphics gfx( pDC->GetSafeHdc() );

		// Define the hilite color, but reduce the alpha for a blended look
		COLORREF crHi = ::GetSysColor(COLOR_HIGHLIGHT);
		Gdiplus::Color clrSel( 100, GetRValue(crHi), GetGValue(crHi),GetBValue(crHi) ); // Note the alpha - 100 (255 is opaque)

		// Define a simple brush with this color...
		Gdiplus::Rect rGPItem(rDraw.left, rDraw.top, rDraw.Width(), rDraw.Height() );
		Gdiplus::SolidBrush brushFill( clrSel );

		// Apply it
		gfx.FillRectangle( &brushFill, rGPItem );
	}
		
	// Draw the checkbox, if appropriate...
	if ( nStyle & TVS_CHECKBOXES )
		this->DrawCheck( pDC, rCheck, this->GetCheckState(hItem) );
}

BOOL CRHTree::HasImage( HTREEITEM hItem )
{
	CImageList*	pIL = this->GetImageList(TVSIL_NORMAL);
	int			nImage = 0;
	int			nSelImage = 0;
	//
	
	if ( pIL )
	{
		// Determine which image this item has...
		if ( this->GetItemImage(hItem, nImage, nSelImage) )
			return TRUE;
	}
	
	return FALSE;	
}

void CRHTree::DrawItemImage( CDC* pDC, CRect rCell, HTREEITEM hItem, BOOL bSelected )
// Draws an item's image from the tree's list
{
	CImageList*	pIL = this->GetImageList(TVSIL_NORMAL);
	CSize		sizeImage( ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON) );
	CRect		rDraw( rCell );
	int			nImage = 0;
	int			nSelImage = 0;
	//
	
	if ( pIL )
	{
		// Determine which image this item has...
		if ( this->GetItemImage(hItem, nImage, nSelImage) )
		{
			// Decide which image we're using...
			if ( bSelected )
				nImage = nSelImage;
				
			if ( nImage >= 0 && nImage < pIL->GetImageCount() )
			{
				rDraw.OffsetRect( -(sizeImage.cx + m_nHSpacer), 0 );
				pIL->DrawEx( pDC, nImage, rDraw.TopLeft(), sizeImage, CLR_NONE, CLR_NONE, ILD_NORMAL );
			}
		}
		
	}
}

void CRHTree::DrawGroupTitle( CDC* pDC, CRect rCell, LPCTSTR lpszTitle )
// You may want special effects for groups - if so, override this
{
	COLORREF		crDraw = this->GetPartColor(eGroupText);
	int				nSaved = pDC->SaveDC();
	//
	
	// Work out where the text is going to go and draw it...
	pDC->SetTextColor( crDraw );
	pDC->DrawText( CString(lpszTitle), rCell, DT_NOPREFIX | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );

	// Put things back as we found them...
	if ( nSaved > 0 )
		pDC->RestoreDC( nSaved );
}

void CRHTree::DrawItemTitle( CDC* pDC, CRect rCell, LPCTSTR lpszTitle )
{
	COLORREF		crDraw = this->GetPartColor(eItemText);
	int				nSaved = pDC->SaveDC();
	//
	
	// Work out where the text is going to go and draw it...
	pDC->SetTextColor( crDraw );
	pDC->DrawText( CString(lpszTitle), rCell, DT_NOPREFIX | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS );

	// Put things back as we found them...
	if ( nSaved > 0 )
		pDC->RestoreDC( nSaved );
}

void CRHTree::DrawItemLines( CDC* pDC, HTREEITEM hItem )
// Each item draws all lines that pass through its "slot" in the display
{
	const LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE );
	const int	nSmallIconWidth = ::GetSystemMetrics(SM_CXSMICON);
	//
	
	// Nothing to do unless lines are ON and we have a parent
	if ( nStyle & TVS_HASLINES )
	{
		HTREEITEM hParent = this->GetParentItem( hItem );
		if ( hParent )
		{
			CRect		rItem;
			CRect		rParent;
			LOGBRUSH	lbInfo;
			int			nSaved = pDC->SaveDC();
			//
			
			// Set up the pen for drawing the lines...
			::ZeroMemory( &lbInfo, sizeof(lbInfo) );
			lbInfo.lbColor = this->IsGroup(hItem) ? this->GetPartColor(eGroupText) : this->GetPartColor(eItemText);
			lbInfo.lbStyle = BS_SOLID;
			CPen pen( PS_COSMETIC | PS_ALTERNATE | PS_JOIN_MITER | PS_ENDCAP_ROUND, 1, &lbInfo );
			pDC->SelectObject( &pen );

			// Get the text rects for both the item and its immediate parent
			this->GetItemRect( hItem, rItem, TRUE );
			this->GetItemRect( hParent, rParent, TRUE );
			
			// Adjust for non-existent buttons
			this->OffsetTextRect( rItem );
			this->OffsetTextRect( rParent );
			
			// Adjust for the image...
			if ( this->HasImage(hItem) )
				rItem.left -= nSmallIconWidth + m_nHSpacer;
			if ( this->HasImage(hParent) )
				rParent.left -= nSmallIconWidth + m_nHSpacer;
			
			// Draw a horizontal line out from the item towards its parent..
			pDC->MoveTo( rItem.left - m_nHSpacer, rItem.CenterPoint().y );
			pDC->LineTo( rParent.left + m_nHSpacer, rItem.CenterPoint().y );
			
			// If we have a sibling, we draw a full vertical line to join up
			// the line coming from the sibling to our parent...
			if ( this->GetNextSiblingItem(hItem) )
			{
				// Note that we stretch one extra pixel in both directions vertically
				// to ensure line continuity...
				pDC->MoveTo( rParent.left + m_nHSpacer, rItem.bottom+1 );
				pDC->LineTo( rParent.left + m_nHSpacer, rItem.top-1 );
			}
			else // No sibling, so just go up towards the parent...
				pDC->LineTo( rParent.left + m_nHSpacer, rItem.top );

			//
			// That takes care of the immediate parent, but we may also need
			// to draw lines to connect earlier ancestors to their children...
			//
			HTREEITEM hPrevParent = hParent;
			hParent = this->GetParentItem( hParent );
			while ( hParent )
			{
				if ( this->GetNextSiblingItem(hPrevParent) )
				{
					// Get the text rectangle for this ancestor...
					this->GetItemRect( hParent, rParent, TRUE );
					
					// Adjust for non-existent buttons
					this->OffsetTextRect( rParent );
					
					// Adjust for the image...
					if ( this->HasImage(hParent) )
						rParent.left -= nSmallIconWidth + m_nHSpacer;
					
					// Note that we stretch one extra pixel in both directions vertically
					// to ensure line continuity...
					pDC->MoveTo( rParent.left + m_nHSpacer, rItem.bottom+1 );
					pDC->LineTo( rParent.left + m_nHSpacer, rItem.top-1 );
				}
				
				// Move on to the next ancestor
				hPrevParent = hParent;
				hParent = this->GetParentItem( hParent );
			}// end of loop
			
			// Put things back as we found them...
			if ( nSaved > 0 )
				pDC->RestoreDC( nSaved );
		}
	}
}

void CRHTree::DrawWidget( CDC* pDC, CRect rCell, BOOL bExpanded, BOOL bActive /*= FALSE*/ )
// Draws the up/down widget from icons that we've produced internally
{
	HICON	hIcon = NULL;
	//

	// Make sure we have our widget images ready for drawing...
	this->PrepareWidgetIcons( pDC );

	// Choose the icon...
	if ( bActive )
		hIcon = bExpanded ? m_hWidgetCollapseHot : m_hWidgetExpandHot;
	else
		hIcon = bExpanded ? m_hWidgetCollapse : m_hWidgetExpand;

	// Draw it...
	::DrawIconEx(	pDC->GetSafeHdc(),
					rCell.left,
					rCell.top,
					hIcon,
					rCell.Width(),
					rCell.Height(),
					0,
					NULL,
					DI_NORMAL );
}

void CRHTree::DrawCheck( CDC* pDC, CRect rCell, int nCheckState )
// Fakes a checkbox, using the themed look if available
{
	// Prepare for theme support.
	this->InitTheme();
	
	// Do we have it?
	if ( m_Theme.GetAppearance() )
	{
		int	nState = 0;
	
		// Translate from the button state to the appropriate draw state flags
		switch ( nCheckState )
		{
			case BST_CHECKED:
				nState = CBS_CHECKEDNORMAL;
			break;
			
			case BST_UNCHECKED:
				nState = CBS_UNCHECKEDNORMAL;
			break;
			
			default: 
				nState = CBS_MIXEDNORMAL;
			break;
		}
		
		// Now do the actual drawing...
		m_Theme.DrawThemeBackground( pDC->GetSafeHdc(), rCell, BP_CHECKBOX, nState );
	}
	else // No themes - just draw it conventionally
	{
		UINT nState = 0;
		
		// Translate from the button state to the appropriate draw state flags
		switch ( nCheckState )
		{
			case BST_CHECKED:
				nState = DFCS_BUTTONCHECK | DFCS_CHECKED;
			break;
			
			case BST_UNCHECKED:
				nState = DFCS_BUTTONCHECK;
			break;
			
			default: 
				nState = DFCS_BUTTON3STATE;
			break;
		}
		
		// Now do the actual drawing...
		pDC->DrawFrameControl( rCell, DFC_BUTTON, nState );
	}
}

void CRHTree::DrawGroupWash( CDC* pDC, CRect rCell )
// You may wish groups to have a different background from normal items
{
	// In this version just color the whole slot...
	pDC->FillSolidRect( rCell, this->GetPartColor(eGroupBack) );
}

BOOL CRHTree::IsGroup( HTREEITEM hItem )
// In my own code, groups are more than just parents, but this
// will do for now. Just override it if you need different criteria.
{
	return this->ItemHasChildren( hItem );
}

int CRHTree::GetCheckState( HTREEITEM hItem )
{
	if ( this->GetCheck(hItem) )
		return BST_CHECKED;
		
	return BST_UNCHECKED;
}

BOOL CRHTree::OnEraseBkgnd(CDC* /*pDC*/)
{
	// return CTreeCtrl::OnEraseBkgnd(pDC);
	return TRUE; // No further action required
}

void CRHTree::OnSize(UINT nType, int cx, int cy)
// Since we've arranged our tree differently, the standard ctrl won't
// get things right...
{
	// Inhibit standard drawing...
	this->SetRedraw( FALSE );
	
	// Handle the size normally...
	CTreeCtrl::OnSize(nType, cx, cy);
	
	// Re-enable drawing..
	this->SetRedraw( TRUE );
	
	// Redraw the whole thing thoroughly in one pass...
	CRect rClient;
	this->GetClientRect( rClient );
	this->RedrawWindow( rClient, NULL, RDW_NOCHILDREN | RDW_UPDATENOW | RDW_INVALIDATE );
}

void CRHTree::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
// Since we've arranged our tree differently, the standard ctrl won't
// get things right...
{
	// Inhibit standard drawing...
	this->SetRedraw( FALSE );
	
	// Handle the scroll normally...
	CTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
	
	// Re-enable drawing..
	this->SetRedraw( TRUE );
	
	// Redraw the whole thing thoroughly in one pass...
	CRect rClient;
	this->GetClientRect( rClient );
	this->RedrawWindow( rClient, NULL, RDW_NOCHILDREN | RDW_UPDATENOW | RDW_INVALIDATE );
}


BOOL CRHTree::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
// Since we've arranged our tree differently, the standard ctrl won't
// get things right...
//
// Added for version 2
{
	// Inhibit standard drawing...
	this->SetRedraw( FALSE );
	
	BOOL bResult = CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);
	
	// Re-enable drawing..
	this->SetRedraw( TRUE );
	
	// Redraw the whole thing thoroughly in one pass...
	CRect rClient;
	this->GetClientRect( rClient );
	this->RedrawWindow( rClient, NULL, RDW_NOCHILDREN | RDW_UPDATENOW | RDW_INVALIDATE );

	return bResult;
}

void CRHTree::OnMouseMove(UINT nFlags, CPoint point)
// Lets us do hover hiliting of the open/close widget
{
	TRACKMOUSEEVENT	tme;
	//

	// Call the inherited method first...
	CTreeCtrl::OnMouseMove(nFlags, point);

	// Take care of group widget hiliting...
	this->HiliteWidget( point );
		
	// We want to know when the mouse leaves, so request a WM_MOUSELEAVE
	memset( &tme, 0, sizeof(tme) );
	tme.cbSize = sizeof(tme);
	tme.dwFlags = TME_LEAVE;
	tme.hwndTrack = m_hWnd;
	::TrackMouseEvent( &tme );
}

LRESULT CRHTree::OnMouseLeave(WPARAM, LPARAM )
{
	// Re-assess widget state
	this->HiliteWidget( CPoint(-1,-1) );
	
	return 0L;
}

void CRHTree::GetWidgetHRange( long& nLeft, long& nRight )
// Returns the horizontal coordinates of the widget "column"
{
	const int	nCXSMIcon = ::GetSystemMetrics(SM_CXSMICON);
	CRect		rClient;
	//

	this->GetClientRect( rClient );
	nRight = rClient.right;
	nLeft = rClient.right - nCXSMIcon;
}

BOOL CRHTree::HitTestWidget( CPoint ptLocal, HTREEITEM& hItem )
// Determines if the point is over a widget. Returns TRUE and the 
// tree item in question if so, otherwise FALSE + NULL
{
	long	nLeft = 0;
	long	nRight = 0;
	//

	// Start by NULLing the return item...
	hItem = NULL;
	
	// Let's do the simplest tests first.
	// First up: is the point in the widget column?
	this->GetWidgetHRange( nLeft, nRight );
	if ( (ptLocal.x <= nRight) && (ptLocal.x >= nLeft) )
	{
		// OK, is the point over an item?
		HTREEITEM hHit = this->HitTest( ptLocal );
		if ( hHit )
		{
			// Is that item a group?
			if ( this->IsGroup(hHit) )
				hItem = hHit; // OK, it's a hit
		}
	}
	
	return (NULL != hItem);
}

BOOL CRHTree::HitTestCheckBox( CPoint ptLocal, HTREEITEM& hItem )
// Determines if the point is over a checkbox. Returns TRUE and the 
// tree item in question if so, otherwise FALSE + NULL
{
	const int	nCXSMIcon = ::GetSystemMetrics(SM_CXSMICON);
	const LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 
	CRect		rClient;
	long		nLeft = 0;
	long		nRight = 0;
	//
	//

	// Start by NULLing the return item...
	hItem = NULL;
	
	// Do we have checkboxes?
	if ( nStyle & TVS_CHECKBOXES )
	{
		// Let's do the simplest tests first.
		// First up: is the point in the checkbox column? The checkbox is to the immediate left
		// of the widget column
		this->GetWidgetHRange( nLeft, nRight );
		nRight = nLeft;
		nLeft -= nCXSMIcon;
		if ( (ptLocal.x <= nRight) && (ptLocal.x >= nLeft) )
		{
			// OK, is the point over an item?
			HTREEITEM hHit = this->HitTest( ptLocal );
			if ( hHit )
				hItem = hHit; // OK, it's a hit
		}
	}
	
	return (NULL != hItem);
}

void CRHTree::HiliteWidget( CPoint ptLocal )
// Triggers a redraw of the item if the hilite state
// of the widget needs to change...
{
	HTREEITEM	hHitItem = NULL;
	//
	
	// Is the point over a widget?
	this->HitTestWidget( ptLocal, hHitItem );

	// Now does this represent a change?
	if ( m_hWidgetHlt != hHitItem )
	{
		// OK, do we have an existing hilited item to unhilite?
		if ( m_hWidgetHlt )
			this->InvalidateItem( m_hWidgetHlt );
			
		// Now, do we have a new item to hilite?
		if ( hHitItem )
			this->InvalidateItem( hHitItem );
		
		// Record the new item...
		m_hWidgetHlt = hHitItem;
	}
}

void CRHTree::InvalidateItem( HTREEITEM hItem )
// Trigger a redraw of a particular item...
{
	CRect	rItem;
	//

	if ( this->GetItemRect(hItem, rItem, FALSE) )
		this->InvalidateRect( rItem );
}

void CRHTree::InvalidateAncestors( HTREEITEM hItem )
// Invalidate this item's ancestors...
{
	hItem = this->GetParentItem( hItem );
	while ( hItem )
	{
		this->InvalidateItem( hItem );
		hItem = this->GetParentItem( hItem );
	}// end of loop
}

void CRHTree::OnLButtonDown(UINT nFlags, CPoint point)
{
	HTREEITEM	hItem = NULL;
	UINT		nHitFlags = 0;
	//
	
	// Take focus
	this->SetFocus();
	
	//
	// From the top:
	// - handle hit on widget
	// - handle hit on checkbox
	// - handle hit elsewhere on item
	//
	if ( this->HitTestWidget(point, hItem) )
		this->Expand( hItem, TVE_TOGGLE );
	else if ( this->HitTestCheckBox(point, hItem) )
	{
		this->SetCheck( hItem, !this->GetCheck(hItem) );
		this->InvalidateItem( hItem);
	}
	else
	{
		hItem = this->HitTest( point, &nHitFlags );
		if ( hItem )
		{
			// We can't let the default handler loose on this, because it
			// still takes care of hits on the non-existent open/close buttons.
			// Also, we'd like selection to work without having to hit the name.
			this->SelectItem( hItem );
		}
		else // Safe to hand over for default processing...
			CTreeCtrl::OnLButtonDown( nFlags, point );
	}
}

void CRHTree::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 
	//
	
	// Do we have checkboxes?
	if ( (nStyle & TVS_CHECKBOXES) && (nChar == VK_SPACE) )
	{
		HTREEITEM hItem = this->GetSelectedItem();
		if ( hItem )
		{
			this->SetCheck( hItem, !this->GetCheck(hItem) );
			this->InvalidateItem( hItem);
			
			// We're done here!
			return;
		}
	}

	// Still here? Handle it normally
	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CRHTree::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 
	//
	
	// We absorbed the SPACE down, play safe and absorb the Up as well
	if ( !(nStyle & TVS_CHECKBOXES) || (nChar != VK_SPACE) )
		CTreeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CRHTree::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const LONG	nStyle = ::GetWindowLong( m_hWnd, GWL_STYLE ); 
	//
	
	// We absorbed the SPACE earlier, let's be consistent here too
	if ( !(nStyle & TVS_CHECKBOXES) || (nChar != VK_SPACE) )
		CTreeCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CRHTree::DestroyWidgetIcons()
{
	::DestroyIcon( m_hWidgetExpand );
	::DestroyIcon( m_hWidgetCollapse );
	::DestroyIcon( m_hWidgetExpandHot );
	::DestroyIcon( m_hWidgetCollapseHot );
	
	m_hWidgetExpand = NULL;
	m_hWidgetCollapse = NULL;
	m_hWidgetExpandHot = NULL;
	m_hWidgetCollapseHot = NULL;
}

void CRHTree::PrepareWidgetIcons( CDC* pDC )
// The widget is held in 4 transparent png images held in resources.
// We load them up and drop them into an image list from which we can extract icons.
//
// This seems like total overkill, but older OS's don't necessarily
// support icons with an alpha channel. By using PNGs and GDI+ we
// get the alph channel antialiasing, and by converting to icons with the right
// background color, we get faster drawing.
{
	const int	nImageWidth = 16;
	const int	nImageHeight = 16;
	//

	if ( !m_hWidgetExpand || !m_hWidgetCollapse || !m_hWidgetExpandHot || !m_hWidgetCollapseHot ||
		 (m_crWidgetBack != this->GetPartColor(eGroupBack)) )
	{
		CImageList	ilTemp;
		CDC			dcOffscreen;	// Memory base device context for flicker free painting
		CBitmap		bmOffscreen;	// The bitmap we paint into
		CBitmap*	pOldBM = NULL;
		//
		
		// Take a note of the current background color
		m_crWidgetBack = this->GetPartColor(eGroupBack);
		
		// Create a temporary image list...
		ilTemp.Create( nImageWidth, nImageHeight, ILC_COLOR24 | ILC_MASK, 0, 1 );
		
		// Create an offscreen workspace
		dcOffscreen.CreateCompatibleDC( pDC );
		bmOffscreen.CreateCompatibleBitmap( pDC, nImageWidth, nImageHeight );
		
		// Let's prepare to return all settings we change
		int nSaveDC = dcOffscreen.SaveDC();
		
		// Select the bitmap into the off-screen DC.
		pOldBM = dcOffscreen.SelectObject( &bmOffscreen );
		
		// Clear to the background color, then draw the expand png onto it
		dcOffscreen.FillSolidRect( 0, 0, nImageWidth, nImageHeight, m_crWidgetBack );
		this->DrawPNG( IDR_EXPAND, &dcOffscreen, 0, 0, nImageWidth, nImageHeight );
		
		// Add it to the image list
		dcOffscreen.SelectObject( pOldBM ); // Disconnect from DC first
		ilTemp.Add( &bmOffscreen, m_crWidgetBack );
		pOldBM = dcOffscreen.SelectObject( &bmOffscreen ); // Reconnect to DC
		
		// Clear to the background color, then produce the "Hot" version
		dcOffscreen.FillSolidRect( 0, 0, nImageWidth, nImageHeight, m_crWidgetBack );
		this->DrawPNG( IDR_EXPANDHOT, &dcOffscreen, 0, 0, nImageWidth, nImageHeight );
		
		// Add it to the image list
		dcOffscreen.SelectObject( pOldBM ); // Disconnect from DC first
		ilTemp.Add( &bmOffscreen, m_crWidgetBack );
		pOldBM = dcOffscreen.SelectObject( &bmOffscreen ); // Reconnect to DC
		
		// Clear to the background color, then draw the collapse png onto it
		dcOffscreen.FillSolidRect( 0, 0, nImageWidth, nImageHeight, m_crWidgetBack );
		this->DrawPNG( IDR_COLLAPSE, &dcOffscreen, 0, 0, nImageWidth, nImageHeight );
		
		// Add it to the image list
		dcOffscreen.SelectObject( pOldBM ); // Disconnect from DC first
		ilTemp.Add( &bmOffscreen, m_crWidgetBack );
		pOldBM = dcOffscreen.SelectObject( &bmOffscreen ); // Reconnect to DC
		
		// Clear to the background color, then produce the "Hot" version
		dcOffscreen.FillSolidRect( 0, 0, nImageWidth, nImageHeight, m_crWidgetBack );
		this->DrawPNG( IDR_COLLAPSEHOT, &dcOffscreen, 0, 0, nImageWidth, nImageHeight );
		
		// Add it to the image list
		dcOffscreen.SelectObject( pOldBM ); // Disconnect from DC first
		ilTemp.Add( &bmOffscreen, m_crWidgetBack );

		// Put things back as they were...
		dcOffscreen.RestoreDC( nSaveDC );
		
		// OK, now get our icons
		this->DestroyWidgetIcons();
		m_hWidgetExpand = ilTemp.ExtractIcon( 0 );
		m_hWidgetExpandHot = ilTemp.ExtractIcon( 1 );
		m_hWidgetCollapse = ilTemp.ExtractIcon( 2 );
		m_hWidgetCollapseHot = ilTemp.ExtractIcon( 3 );
	}
}

BOOL CRHTree::DrawPNG( UINT nIDPNG, CDC* pDC, int nLeft, int nTop, int nWidth, int nHeight )
// Uses GDI+ to load up and draw a png
{
	USES_CONVERSION;
	BOOL	bResult = FALSE;
	//

	// Pull the resource out to a temp file...
	CString	strFile( CResourceUtils::UnpackResToTempFile(nIDPNG, _T("PNG")) );
	
	// Use a separate stack frame to ensure that the file is not in use
	// when we come to delete it...
	{
		// Use GDI+ to load the bitmap and draw it
		Gdiplus::Bitmap bm( A2CW(strFile), FALSE ); // Note: Unicode path required
		Gdiplus::Graphics gfx( pDC->GetSafeHdc() );
		Gdiplus::Rect rImage( nLeft, nTop, nWidth, nHeight );
		Gdiplus::Status nStatus = gfx.DrawImage( &bm, rImage );
		bResult = (Gdiplus::Ok == nStatus);
	}

	// Ditch the file...
	::DeleteFile( strFile );

	return bResult;
}

BOOL CRHTree::OnToolTipText( UINT /*id*/, NMHDR* pNMHDR, LRESULT* pResult )
// The tooltips can be obstructive if the user has the mouse over
// the widget or checkbox. Let's zap the TT text if the mouse is
// over those areas...
{
	TOOLTIPTEXTA*		pTTTA = (TOOLTIPTEXTA*)pNMHDR; // For ANSI versions of the msg
	TOOLTIPTEXTW*		pTTTW = (TOOLTIPTEXTW*)pNMHDR; // For Wide versions of the msg
	HTREEITEM			hUnused = NULL;
	long				nWidgetLeft = 0;
	long				nWidgetRight = 0;
	//

	// Set the result now...
	*pResult = 0;

	// Determine location of mouse
	DWORD dwPos = ::GetMessagePos();
	CPoint ptMouse = CPoint( GET_X_LPARAM(dwPos), GET_Y_LPARAM(dwPos) );
	this->ScreenToClient( &ptMouse );
	
	// Determine the horizontal coordinates of the widget column
	this->GetWidgetHRange( nWidgetLeft, nWidgetRight );
	
	// Don't display any text for the widget or checkbox!
	if ( this->HitTestCheckBox(ptMouse, hUnused) || (ptMouse.x >= nWidgetLeft) )
	{
		// Possibly unnecessary, but let's make certain the text is blank
		if ( TTN_NEEDTEXTA == pNMHDR->code )
		{
			pTTTA->lpszText = NULL;
			::ZeroMemory( pTTTA->szText, sizeof(pTTTA->szText) );
		}
		else if ( TTN_NEEDTEXTW == pNMHDR->code )
		{
			pTTTW->lpszText = NULL;
			::ZeroMemory( pTTTW->szText, sizeof(pTTTW->szText) );
		}
		
		// We've handled this...
		return TRUE;
	}
	
	return FALSE;
}

BOOL CRHTree::EnsureVisible( HTREEITEM hItem )
// EnsureVisible may cause horizontal scrolling, which in turn
// requires a redraw to ensure correct appearance...
//
// Added for version 2
{
	// Inhibit standard drawing...
	this->SetRedraw( FALSE );
	
	BOOL bResult = CTreeCtrl::EnsureVisible( hItem );
	
	// Re-enable drawing..
	this->SetRedraw( TRUE );
	
	// Redraw the whole thing thoroughly in one pass...
	CRect rClient;
	this->GetClientRect( rClient );
	this->RedrawWindow( rClient, NULL, RDW_NOCHILDREN | RDW_UPDATENOW | RDW_INVALIDATE );

	return bResult;
}
