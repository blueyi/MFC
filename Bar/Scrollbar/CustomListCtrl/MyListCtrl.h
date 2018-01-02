
#pragma once


class CMyListCtrl: 
	public CWindowImpl< CMyListCtrl, CListViewCtrl >,
	public CCustomDraw< CMyListCtrl >
{

public:

	///
	/// Constructor
	///
	CMyListCtrl();

public:

	///
	/// Message map
	///

	BEGIN_MSG_MAP( CMyListCtrl )

		CHAIN_MSG_MAP_ALT( CCustomDraw< CMyListCtrl >, 1 )

		MESSAGE_HANDLER( WM_ERASEBKGND, OnEraseBkgnd )
		MESSAGE_HANDLER( WM_KEYDOWN, OnKeyDown )
		MESSAGE_HANDLER( WM_LBUTTONDOWN, OnLButtonDown )
		MESSAGE_HANDLER( WM_CREATE, OnCreate )
		MESSAGE_HANDLER( WM_VSCROLL, OnVScroll )
		MESSAGE_HANDLER( OCM_MEASUREITEM, OnMeasureItem )

		REFLECTED_NOTIFY_CODE_HANDLER( LVN_ITEMACTIVATE, OnItemActivate );

	END_MSG_MAP()

public:

	///
	/// Message handlers
	///

	LRESULT OnEraseBkgnd
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnKeyDown
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnLButtonDown
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnContextMenu
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnVScroll
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnMeasureItem
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnSetFont
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnCreate
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnItemActivate( int idCtrl, LPNMHDR pnmh, BOOL& bHandled );

public:

	///
	/// Methods
	///

	///
	/// OnPrePaint
	///
	DWORD OnPrePaint( int idCtrl, LPNMCUSTOMDRAW nmcd );


public:

	///
	/// getIndexOffset
	///
	/// Get item index offset ( first visible item )
	///
	int getIndexOffset() const;


	///
	/// setIndexOffset
	///
	/// Set item index offset ( first visible item )
	///
	/// @param indexOffset - item index offset
	/// @param updateScrollbar - flag which indicates 
	///			if it is required to update scrollbar 
	///
	void setIndexOffset
		( 
			const int indexOffset, 
			const bool updateScrollbar = true 
		);


	///
	/// setVScrollbar
	///
	/// Set vertical scrollbar HWND to manage
	///
	void setVScrollbar( const HWND hScrollbar );


	///
	/// updateVScrollbarPos
	///
	/// Update vertical scrollbar position
	///
	/// @param pos - new scrollbar position
	///
	void updateVScrollbar( const int pos );

	///
	/// Members
	///

private:

	int m_IndexOffset;

	HWND m_Scrollbar;

	CBitmap  m_MenuHighlight;
};


///
/// getIndexOffset
///
/// Get item's index offset ( first visible item )
///
inline
int CMyListCtrl::getIndexOffset() const
{
	return m_IndexOffset;
}
