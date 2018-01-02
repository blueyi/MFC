
#include "stdafx.h"
#include "MyScrollBar.h"

#include "resource.h"


//////////////////////////////////////////////////////////////////////////
///
/// CMyScrollbar
///


///
/// Constructor
///
CMyScrollbar::CMyScrollbar():
	m_State( NONE ),
	m_DragOffset( -1 ),
	m_DragPos( -1 ),
	m_Buddy( NULL ),
	m_ClickPos( -1, -1 ),
	m_Timer( NULL )
{
	Init();
}


///
/// Init
///
/// Initialize scrollbar image
///
void CMyScrollbar::Init()
{
	// Back bitmap
	m_Back.LoadBitmap( IDB_SCROLL_BACK );

	// Up arrow bitmap
	m_UpArrow.LoadBitmap( IDB_SCROLL_UP );

	// Down arrow bitmap
	m_DownArrow.LoadBitmap( IDB_SCROLL_DOWN );

	// Scroll widget bitmap
	m_ScrollWidget.LoadBitmap( IDB_SCROLL_THUMB );
}


LRESULT CMyScrollbar::OnPaint
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	CPaintDC dc( m_hWnd );

	CRect clientRect;
	GetClientRect( clientRect );

	CMemoryDC memDC( dc, clientRect );

	HBRUSH hBrush = ( HBRUSH ) ::SendMessage
		( 
			GetParent(), 
			WM_CTLCOLORSCROLLBAR, 
			( WPARAM ) ( ( HDC ) dc ), 
			( LPARAM ) m_hWnd 
		);
	_ASSERT( hBrush != NULL );

	memDC.FillRect( clientRect, hBrush );

	CRect rect;
	CSize bmpSize;

	CDC memBitmapDC = CreateCompatibleDC( dc );
	HBITMAP prevBitmap = NULL;

	// Up arrow
	calcUpArrowRect( rect );
	m_UpArrow.GetSize( bmpSize );
	memBitmapDC.SelectBitmap( m_UpArrow );
	memDC.BitBlt
		( 
			rect.left,
			rect.top,
			bmpSize.cx,
			bmpSize.cy,
			memBitmapDC,
			0,
			0,
			SRCCOPY
		);

	// Back
	calcBackRect( rect );
	m_Back.GetSize( bmpSize );
	memBitmapDC.SelectBitmap( m_Back );
	memDC.BitBlt
		( 
			rect.left,
			rect.top,
			bmpSize.cx,
			bmpSize.cy,
			memBitmapDC,
			0,
			0,
			SRCCOPY
		);

	// Down arrow
	calcDownArrowRect( rect );
	m_DownArrow.GetSize( bmpSize );
	memBitmapDC.SelectBitmap( m_DownArrow );
	memDC.BitBlt
		( 
			rect.left,
			rect.top,
			bmpSize.cx,
			bmpSize.cy,
			memBitmapDC,
			0,
			0,
			SRCCOPY
		);

	// Scroll widget
	calcScrollWidgetRect( rect );

	if ( m_State == SCROLL_WIDGET )
	{
		// Scroll widget is captured
		rect.MoveToY( m_DragPos );
	}

	m_ScrollWidget.GetSize( bmpSize );
#ifdef _WIN32_WCE
	::TransparentImage
		(
			memDC,
			rect.left,
			rect.top,
			bmpSize.cx,
			bmpSize.cy,
			m_ScrollWidget,
			0,
			0,
			bmpSize.cx,
			bmpSize.cy,
			RGB( 255, 255, 255 )
		);
#else
	memBitmapDC.SelectBitmap( m_ScrollWidget );
	memDC.TransparentBlt
		(
			rect.left,
			rect.top,
			bmpSize.cx,
			bmpSize.cy,
			memBitmapDC,
			0,
			0,
			bmpSize.cx,
			bmpSize.cy,
			RGB( 255, 255, 255 )
		);
#endif // _WIN32_WCE

	memBitmapDC.SelectBitmap( prevBitmap );

	return 0;
}


LRESULT CMyScrollbar::OnLButtonDown
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	const CPoint pos( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

	CRect upArrowRect;
	calcUpArrowRect( upArrowRect );
	CRect downArrowRect;
	calcDownArrowRect( downArrowRect );
	CRect scrollWidgetRect;
	calcScrollWidgetRect( scrollWidgetRect );
	CRect backRect;
	calcBackRect( backRect );

	if ( upArrowRect.PtInRect( pos ) )
	{
		m_State = UP_ARROW;

		SendMessage
			(
				( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
				WM_VSCROLL,
				MAKEWPARAM( SB_LINEUP, 0 ),
				( LPARAM ) m_hWnd 
			);
	}
	else if ( downArrowRect.PtInRect( pos ) )
	{
		m_State = DOWN_ARROW;

		SendMessage
			(
				( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
				WM_VSCROLL,
				MAKEWPARAM( SB_LINEDOWN, 0 ),
				( LPARAM ) m_hWnd 
			);
	}
	else if ( scrollWidgetRect.PtInRect( pos ) )
	{
		m_State = SCROLL_WIDGET;
		m_DragOffset = pos.y - scrollWidgetRect.top;
		m_DragPos = scrollWidgetRect.top;
	}
	else if ( backRect.PtInRect( pos ) )
	{
		if ( pos.y < scrollWidgetRect.top )
		{
			m_State = BACK_UP;

			SendMessage
				(
					( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
					WM_VSCROLL,
					MAKEWPARAM( SB_PAGEUP, 0 ),
					( LPARAM ) m_hWnd 
				);
		}
		else if ( pos.y >= scrollWidgetRect.bottom )
		{
			m_State = BACK_DOWN;
			SendMessage
				(
					( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
					WM_VSCROLL,
					MAKEWPARAM( SB_PAGEDOWN, 0 ),
					( LPARAM ) m_hWnd 
				);
		}
		else
		{
			m_State = NONE;
		}
	}
	else
	{
		m_State = NONE;
	}

	if ( m_State != SCROLL_WIDGET )
	{
		if ( m_Timer != NULL )
		{
			BOOL resKT = KillTimer( 1000 );
			_ASSERT( resKT );

			m_Timer = NULL;
		}

		m_ClickPos = pos;

		m_Timer = SetTimer( 1000, 100, NULL );
		_ASSERT( m_Timer != NULL );
	}

	SetCapture();

	return 0;
}


LRESULT CMyScrollbar::OnLButtonUp
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	if ( m_State == SCROLL_WIDGET )
	{
		const int nPos = calcThumbPos( m_DragPos );

		SendMessage
			(
				( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
				WM_VSCROLL,
				MAKEWPARAM( SB_THUMBPOSITION, nPos ),
				( LPARAM ) m_hWnd
			);
	}

	if ( m_State != NONE )
	{
		SendMessage
			( 
				( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
				WM_VSCROLL, 
				MAKEWPARAM( SB_ENDSCROLL, 0 ), 
				( LPARAM ) m_hWnd 
			);

		m_State = NONE;

		Invalidate();
	}

	if ( m_Timer != NULL )
	{
		m_ClickPos = CPoint( -1, -1 );

		BOOL resKT = KillTimer( 1000 );
		_ASSERT( resKT );

		m_Timer = NULL;
	}

	ReleaseCapture();

	return 0;
}


LRESULT CMyScrollbar::OnMouseMove
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	m_ClickPos = CPoint( GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) );

	const CPoint& pos = m_ClickPos;

	if ( m_State == SCROLL_WIDGET )
	{
		CRect backRect;
		calcBackRect( backRect );

		if ( ( pos.y >= backRect.top ) && ( pos.y <= backRect.bottom ) )
		{
			const int prevDragPos = m_DragPos;
			m_DragPos = pos.y - m_DragOffset;

			if ( m_DragPos != prevDragPos )
			{
				CRect scrollWidgetRect;
				calcScrollWidgetRect( scrollWidgetRect );
				backRect.bottom -= scrollWidgetRect.Height();

				if ( m_DragPos < backRect.top )
				{
					m_DragPos = backRect.top;
				}
				else if ( m_DragPos >= backRect.bottom )
				{
					m_DragPos = backRect.bottom;
				}

				// Calculate nPos value
				const int prevNPos = calcThumbPos( prevDragPos );
				const int nPos = calcThumbPos( m_DragPos );

				if ( nPos != prevNPos )
				{
					SendMessage
						(
							( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
							WM_VSCROLL,
							MAKEWPARAM( SB_THUMBTRACK, nPos ),
							( LPARAM ) m_hWnd
						);
				}

				Invalidate();
			}
		}
	}

	return 0;
}


LRESULT CMyScrollbar::OnEraseBkgnd
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	// Note: as WM_CTLCOLORSCROLLBAR is not sent by OS (under WinCE), 
	// we have to emulate the required behavior.
	// We send this message from WM_PAINT handler, 
	// get the brush to erase the background.
	return TRUE;
}


LRESULT CMyScrollbar::OnSetScrollInfo
	( 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam, 
		BOOL& /*bHandled*/ 
	)
{
	const BOOL fRedraw = ( BOOL ) wParam;

	LRESULT res = DefWindowProc( uMsg, ( WPARAM ) FALSE, lParam );

	if ( fRedraw )
	{
		Invalidate();
	}

	return res;
}


///
/// getUpArrowRect
///
/// Get up arrow rectangle
///
void CMyScrollbar::calcUpArrowRect( CRect& rect )
{
	_ASSERT( GetObjectType( m_UpArrow ) == OBJ_BITMAP );

	CSize bmpSize;
	m_UpArrow.GetSize( bmpSize );

	rect = CRect( CPoint( 0, 0 ), bmpSize );
}


///
/// getDownArrowRect
///
/// Get down arrow rectangle
///
void CMyScrollbar::calcDownArrowRect( CRect& rect )
{
	_ASSERT( GetObjectType( m_DownArrow ) == OBJ_BITMAP );

	CRect backRect;
	calcBackRect( backRect );

	CSize bmpSize;
	m_DownArrow.GetSize( bmpSize );

	rect = CRect( CPoint( 0, backRect.bottom ), bmpSize );
}


///
/// getBackRect
///
/// Get back rectangle
///
void CMyScrollbar::calcBackRect( CRect& rect )
{
	_ASSERT( GetObjectType( m_Back ) == OBJ_BITMAP );

	CRect upArrowRect;
	calcUpArrowRect( upArrowRect );

	CSize bmpSize;
	m_Back.GetSize( bmpSize );

	rect = CRect( CPoint( 0, upArrowRect.bottom ), bmpSize );
}


///
/// getScrollWidgetRect
///
/// Get scroll widget rectangle
///
void CMyScrollbar::calcScrollWidgetRect( CRect& rect )
{
	CRect scrollRect;
	calcBackRect( scrollRect );

	_ASSERT( GetObjectType( m_ScrollWidget ) == OBJ_BITMAP );

	CSize bmpSize;
	m_ScrollWidget.GetSize( bmpSize );

	// Available rectangle for scrolling
	scrollRect.bottom -= bmpSize.cy;

	if ( scrollRect.Height() > 0 )
	{
		SCROLLINFO si;
		::ZeroMemory( &si, sizeof( si ) );
		si.cbSize = sizeof( si );
		si.fMask = SIF_ALL;
		GetScrollInfo( &si );

		const int posDiff = si.nPos - si.nMin;
		int minMaxDiff = si.nMax - si.nMin;
		if ( minMaxDiff == 0 )
		{
			minMaxDiff = 1;
		}

		rect = CRect
			( 
				CPoint
					( 
						0, 
						scrollRect.top + posDiff * scrollRect.Height() / minMaxDiff 
					), 
				bmpSize
			);
		_ASSERT( rect.top >= 0 && rect.top <= scrollRect.bottom );
	}
	else
	{
		// There is nothing to scroll
		_ASSERT( false );
		rect = CRect( 0, 0, 0, 0 );
	}
}


///
/// calcThumbPos
///
/// Calculate current thumb position depend on drag position
///
int CMyScrollbar::calcThumbPos( const int dragPos )
{
	SCROLLINFO si;
	::ZeroMemory( &si, sizeof( si ) );
	si.cbSize = sizeof( si );
	si.fMask = SIF_RANGE;
	GetScrollInfo( &si );

	CRect backRect;
	calcBackRect( backRect );
	CRect scrollWidgetRect;
	calcScrollWidgetRect( scrollWidgetRect );
	backRect.bottom -= scrollWidgetRect.Height();

	const int perc = ( dragPos - backRect.top ) * 100 / backRect.Height();
	const int nPos = si.nMin + ( si.nMax - si.nMin ) * perc / 100;

	_ASSERT( nPos >= si.nMin && nPos <= si.nMax );
	return nPos;
}


LRESULT CMyScrollbar::OnLButtonDblClk
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	return 0;
}


LRESULT CMyScrollbar::OnTimer
	( 
		UINT /*uMsg*/, 
		WPARAM /*wParam*/, 
		LPARAM /*lParam*/, 
		BOOL& /*bHandled*/ 
	)
{
	CRect upArrowRect;
	calcUpArrowRect( upArrowRect );
	CRect downArrowRect;
	calcDownArrowRect( downArrowRect );
	CRect scrollWidgetRect;
	calcScrollWidgetRect( scrollWidgetRect );
	CRect backRect;
	calcBackRect( backRect );

	// This function doesn't work on WinCE, so we use our own click position
	//BOOL resGCP = GetCursorPos( &pos );
	//_ASSERT( resGCP == TRUE );
	//ScreenToClient( &pos );
	const CPoint& pos = m_ClickPos;

	switch ( m_State )
	{
		case UP_ARROW:
			{
				if ( upArrowRect.PtInRect( pos ) )
				{
					SendMessage
						(
							( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
							WM_VSCROLL,
							MAKEWPARAM( SB_LINEUP, 0 ),
							( LPARAM ) m_hWnd 
						);
				}
			}
			break;

		case DOWN_ARROW:
			{
				if ( downArrowRect.PtInRect( pos ) )
				{
					SendMessage
						(
							( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
							WM_VSCROLL,
							MAKEWPARAM( SB_LINEDOWN, 0 ),
							( LPARAM ) m_hWnd 
						);
				}
			}
			break;

		case SCROLL_WIDGET:
			// Nothing should be done
			break;

		case BACK_UP:
			{
				if ( backRect.PtInRect( pos ) )
				{
					if ( pos.y < scrollWidgetRect.top )
					{
						SendMessage
							(
								( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
								WM_VSCROLL,
								MAKEWPARAM( SB_PAGEUP, 0 ),
								( LPARAM ) m_hWnd 
							);
					}
				}
			}
			break;

		case BACK_DOWN:
			{
				if ( backRect.PtInRect( pos ) )
				{
					if ( pos.y >= scrollWidgetRect.bottom )
					{
						SendMessage
							(
								( ( m_Buddy == NULL ) ? GetParent() : m_Buddy ), 
								WM_VSCROLL,
								MAKEWPARAM( SB_PAGEDOWN, 0 ),
								( LPARAM ) m_hWnd 
							);
					}
				}
			}
			break;
	}

	return 0;
}
