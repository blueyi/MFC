
#include "stdafx.h"
#include "MyListCtrl.h"

#include "resource.h"


//////////////////////////////////////////////////////////////////////////
///
/// CMyListCtrl
///

CMyListCtrl::CMyListCtrl():
	m_IndexOffset( 0 ),
	m_Scrollbar( NULL )
{
	m_MenuHighlight.LoadBitmap( IDB_MENU_HIGHLIGHT );
}


DWORD CMyListCtrl::OnPrePaint( int /*idCtrl*/, LPNMCUSTOMDRAW nmcd )
{
	_ASSERT( nmcd != NULL );
	//LPNMLVCUSTOMDRAW nmlvcd = ( LPNMLVCUSTOMDRAW ) nmcd;

	CDCHandle dc( nmcd->hdc );
	dc.SetBkMode( TRANSPARENT );

	CRect clipRect;
	dc.GetClipBox( clipRect );

	const int indexOffset = getIndexOffset();
	const int countPerPage = GetCountPerPage();
	const int countTotal = GetItemCount();
	const int count = min( countPerPage, countTotal - indexOffset );

	for ( int i = 0; i < count; ++i )
	{
		const int rectIndex = i;
		_ASSERT( rectIndex >= 0 && rectIndex < GetItemCount() );

		// Item rectangle
		CRect boundsRect;
		GetItemRect( rectIndex, boundsRect, LVIR_BOUNDS );
		CRect labelRect;
		GetItemRect( rectIndex, labelRect, LVIR_LABEL );

		CRect interRect;
		if ( interRect.IntersectRect( boundsRect, clipRect ) )
		{
			const int itemIndex = i + indexOffset;
			_ASSERT( itemIndex >= 0 && itemIndex < GetItemCount() );

			// Item state
			const UINT itemState = GetItemState( itemIndex, LVIS_SELECTED );

			// Item text
			CString text;
			GetItemText( itemIndex, 0, text );

			// Draw item
			const COLORREF textColor = 
				( itemState & LVIS_SELECTED )
				?
				RGB( 0, 0, 0 )
				:
				RGB( 255, 255, 255 )
				;

			if ( itemState & LVIS_SELECTED )
			{
				CSize bmpSize;
				m_MenuHighlight.GetSize( bmpSize );

				CDC memDC = CreateCompatibleDC( dc );
				HBITMAP prevBitmap = memDC.SelectBitmap( m_MenuHighlight );
#ifdef _WIN32_WCE
				dc.BitBlt
					( 
						boundsRect.left, 
						boundsRect.top,
						bmpSize.cx,
						bmpSize.cy,
						memDC,
						0,
						0,
						SRCPAINT
					);
#else
				BLENDFUNCTION blendFunc;
				::ZeroMemory( &blendFunc, sizeof( blendFunc ) );
				blendFunc.BlendOp = AC_SRC_OVER;
				blendFunc.SourceConstantAlpha = 128;
				dc.AlphaBlend
					( 
						boundsRect.left, 
						boundsRect.top,
						bmpSize.cx,
						bmpSize.cy,
						memDC,
						0,
						0,
						bmpSize.cx,
						bmpSize.cy,
						blendFunc
					);
#endif // _WINCE_WIN32
				memDC.SelectBitmap( prevBitmap );
			}

			CRect rect = boundsRect;
			rect.left = labelRect.left + 20;

			dc.SetTextColor( textColor );
			dc.DrawText
				( 
					text, 
					text.GetLength(), 
					rect, 
					DT_SINGLELINE | DT_VCENTER 
				);
		}
	}

	return CDRF_DODEFAULT;
}


LRESULT CMyListCtrl::OnEraseBkgnd
	( 
		UINT /*uMsg*/, 
		WPARAM wParam, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	_ASSERT( wParam != NULL );
	CDCHandle dc( ( HDC ) wParam );

	CBrushHandle brush = ( HBRUSH ) SendMessage
		( 
			GetParent(), 
			WM_CTLCOLORSTATIC, 
			( WPARAM ) ( HDC ) dc, 
			( LPARAM ) m_hWnd 
		);

	CRect rect;
	GetClientRect( rect );

	if ( brush == NULL )
	{
		// Can't get the brush from the parent window
		_ASSERT( brush != NULL );
		// Use default
		brush = ( HBRUSH ) GetStockObject( WHITE_BRUSH );
	}

	dc.FillRect( rect, brush );

	return TRUE;
}


LRESULT CMyListCtrl::OnKeyDown
	(
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	const int prevSelectedIndex = GetSelectedIndex();

	LRESULT res = DefWindowProc( uMsg, wParam, lParam );

	// Find selected item
	const int selectedItemIndex = GetSelectedIndex();

	if ( selectedItemIndex != prevSelectedIndex )
	{
		const int countOfVisibleItems = GetCountPerPage();
		const int firstVisibleItem = getIndexOffset();

		if ( selectedItemIndex < firstVisibleItem )
		{
			setIndexOffset( selectedItemIndex );
		}
		else if ( selectedItemIndex >= firstVisibleItem + countOfVisibleItems )
		{
			setIndexOffset( selectedItemIndex - countOfVisibleItems + 1 );
		}

		const int indexOffset = getIndexOffset();

		// Update selected items
		CRect selItemRect;
		GetItemRect
			( 
				selectedItemIndex - indexOffset, 
				selItemRect, 
				LVIR_BOUNDS 
			);
		CRect prevSelItemRect;
		GetItemRect
			( 
				prevSelectedIndex - indexOffset, 
				prevSelItemRect, 
				LVIR_BOUNDS 
			);

		CRect combRect;
		combRect.UnionRect( selItemRect, prevSelItemRect );
		InvalidateRect( combRect );
	}

	return res;
}


LRESULT CMyListCtrl::OnLButtonDown
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	const CPoint pos( LOWORD( lParam ), HIWORD( lParam ) );

#ifdef _WIN32_WCE
	SHRGINFO shrgi = { sizeof( SHRGINFO ), m_hWnd, pos.x, pos.y, 0 };
	// Try to recognize gesture
	if ( SHRecognizeGesture( &shrgi ) == 0 )
#endif // _WIN32_WCE
	{
		const int prevSelectedIndex = GetSelectedIndex();
		int selectedItemIndex = -1;

		const int indexOffset = getIndexOffset();
		const int countPerPage = GetCountPerPage();
		const int countTotal = GetItemCount();
		const int count = min( countPerPage, countTotal - indexOffset );

		// find selected item
		for ( int i = 0; i < count; ++i )
		{
			const int rectIndex = i;
			_ASSERT( rectIndex >= 0 && rectIndex < GetItemCount() );

			// Item rectangle
			CRect boundsRect;
			GetItemRect( rectIndex, boundsRect, LVIR_BOUNDS );

			if ( boundsRect.PtInRect( pos ) == TRUE )
			{
				selectedItemIndex = indexOffset + i;
				break;
			}
		}

		if ( selectedItemIndex != -1 )
		{
			if ( selectedItemIndex != prevSelectedIndex )
			{
				// Invalidate previously selected item
				if ( 
						( prevSelectedIndex >= indexOffset ) 
						&& 
						( prevSelectedIndex < indexOffset + GetCountPerPage() ) 
					)
				{
					CRect prevSelItemRect;
					GetItemRect
						( 
							prevSelectedIndex - indexOffset, 
							prevSelItemRect, 
							LVIR_BOUNDS 
						);

					InvalidateRect( prevSelItemRect );
				}

				// Invalidate selected item
				if ( 
						( selectedItemIndex >= indexOffset ) 
						&& 
						( selectedItemIndex < indexOffset + GetCountPerPage() ) 
					)
				{
					CRect selItemRect;
					GetItemRect
						( 
							selectedItemIndex - indexOffset, 
							selItemRect, 
							LVIR_BOUNDS 
						);

					InvalidateRect( selItemRect );
				}

				SelectItem( selectedItemIndex );
			}
		}

	}

	return 0;
}


///
/// setIndexOffset
///
/// Set item index offset ( first visible item )
///
/// @param indexOffset - item index offset
/// @param updateScrollbar - flag which indicates if it is required to update scrollbar 
///
void CMyListCtrl::setIndexOffset
	(
		const int indexOffset, 
		const bool updateScrollbar 
	)
{
	if ( indexOffset != m_IndexOffset )
	{
		// Update item
		m_IndexOffset = indexOffset;
		Invalidate();
	}

	// Update scrollbar
	if ( ( m_Scrollbar != NULL ) && updateScrollbar )
	{
		::SetScrollPos( m_Scrollbar, SB_CTL, getIndexOffset(), TRUE );
	}
}


LRESULT CMyListCtrl::OnVScroll
	( 
		UINT /*uMsg*/, 
		WPARAM wParam, 
		LPARAM  /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	LRESULT res = 0;

	const int scrollCode = ( int ) LOWORD( wParam );

	switch ( scrollCode )
	{
		case SB_TOP:
			setIndexOffset( 0 );
			break;

		case SB_BOTTOM:
			setIndexOffset( GetItemCount() - GetCountPerPage() );
			break;

		case SB_LINEUP:
			{
				int indexOffset = getIndexOffset();
				if ( indexOffset > 0 )
				{
					setIndexOffset( --indexOffset );
				}
			}
			break;

		case SB_LINEDOWN:
			{
				int indexOffset = getIndexOffset();
				if ( indexOffset < ( GetItemCount() - GetCountPerPage() ) )
				{
					setIndexOffset( ++indexOffset );
				}
			}
			break;

		case SB_PAGEUP:
			{
				int indexOffset = getIndexOffset();
				indexOffset -= GetCountPerPage();
				if ( indexOffset < 0 )
				{
					indexOffset = 0;
				}
				setIndexOffset( indexOffset );
			}
			break;

		case SB_PAGEDOWN:
			{
				int indexOffset = getIndexOffset();
				indexOffset += GetCountPerPage();
				if ( indexOffset > ( GetItemCount() - GetCountPerPage() ) )
				{
					indexOffset = GetItemCount() - GetCountPerPage();
				}

				setIndexOffset( indexOffset );
			}
			break;

		case SB_THUMBTRACK:
			{
				const short int scrollPos = ( short int ) HIWORD( wParam );
				setIndexOffset( scrollPos, false );
			}
			break;

		case SB_THUMBPOSITION:
			{
				const short int scrollPos = ( short int ) HIWORD( wParam );
				setIndexOffset( scrollPos );
			}
			break;

		default:
			res = TRUE;
	}

	return res;
}


LRESULT CMyListCtrl::OnMeasureItem
	( 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM  lParam, 
		BOOL& /*bHandled*/ 
	)
{
	_ASSERT( lParam != NULL );
	LPMEASUREITEMSTRUCT lpmis = ( LPMEASUREITEMSTRUCT ) lParam;

	if ( m_MenuHighlight != NULL )
	{
		_ASSERT( GetObjectType( m_MenuHighlight ) == OBJ_BITMAP );

		CSize bmpSize;
		m_MenuHighlight.GetSize( bmpSize );

		if ( lpmis->itemHeight < ( UINT ) bmpSize.cy )
		{
			lpmis->itemHeight = bmpSize.cy;
		}
	}

	return DefWindowProc( uMsg, wParam, ( LPARAM ) lpmis );
}


LRESULT CMyListCtrl::OnCreate
	( 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	LPCREATESTRUCT lpcs = ( LPCREATESTRUCT ) lParam;

	const DWORD styleMods = 
		LVS_REPORT 
		| 
		LVS_OWNERDRAWFIXED 
		| 
		LVS_NOCOLUMNHEADER 
		| 
		LVS_SINGLESEL 
		| 
		LVS_NOSCROLL 
		| 
		LVS_SHOWSELALWAYS
		;

	ModifyStyle( 0, styleMods );

	lpcs->style = GetStyle();
	LRESULT res = DefWindowProc( uMsg, wParam, ( LPARAM ) lpcs );

	InsertColumn( 0, _T( "Column" ), LVCFMT_LEFT );
	SetColumnWidth( 0, LVSCW_AUTOSIZE_USEHEADER );

	return res;
}


///
/// setVScrollbar
///
/// Set vertical scrollbar HWND to manage
///
void CMyListCtrl::setVScrollbar( const HWND hScrollbar )
{
	_ASSERT( ::IsWindow( hScrollbar ) );
	m_Scrollbar = hScrollbar;

	// Initialize scroll bar
	const int totalCount = GetItemCount();
	const int visibleCount = GetCountPerPage();

	if ( totalCount > visibleCount )
	{
		::ShowWindow( m_Scrollbar, SW_SHOW );
		::SetScrollRange
			( 
				m_Scrollbar, 
				SB_CTL, 
				0, 
				totalCount - visibleCount, 
				FALSE 
			);

		setIndexOffset( 0 );
	}
	else
	{
		::ShowWindow( m_Scrollbar, SW_HIDE );
	}

}

///
/// updateVScrollbarPos
///
/// Update vertical scrollbar position
///
/// @param pos - new scrollbar position
///
void CMyListCtrl::updateVScrollbar( const int pos )
{
	if ( m_Scrollbar != NULL )
	{
		::SetScrollPos( m_Scrollbar, SB_CTL, pos, TRUE );
	}
	else
	{
		_ASSERT( false );
	}
}


LRESULT CMyListCtrl::OnItemActivate
	(
		int /*idCtrl*/, 
		LPNMHDR /*pnmh*/, 
		BOOL& /*bHandled*/ 
	)
{
	return 0;
}
