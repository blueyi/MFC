
#pragma once


//////////////////////////////////////////////////////////////////////////
///
/// CMyScrollbar

class CMyScrollbar:
	public CWindowImpl< CMyScrollbar, CScrollBar, CControlWinTraits >
{

public:

	///
	/// Constructor
	///
	CMyScrollbar();


	///
	/// Init
	///
	/// Initialize scrollbar images
	///
	void Init();

public:

	///
	/// Message map
	///

	BEGIN_MSG_MAP( CMyScrollbar )

		MESSAGE_HANDLER( WM_PAINT, OnPaint )
		MESSAGE_HANDLER( WM_LBUTTONDOWN, OnLButtonDown )
		MESSAGE_HANDLER( WM_LBUTTONUP, OnLButtonUp )
		MESSAGE_HANDLER( WM_MOUSEMOVE, OnMouseMove )

		MESSAGE_HANDLER( SBM_SETSCROLLINFO, OnSetScrollInfo )
		MESSAGE_HANDLER( WM_LBUTTONDBLCLK, OnLButtonDblClk )

		MESSAGE_HANDLER( WM_ERASEBKGND, OnEraseBkgnd )

		MESSAGE_HANDLER( WM_TIMER, OnTimer )

	END_MSG_MAP()

public:

	///
	/// Message handlers
	///

	LRESULT OnPaint
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


	LRESULT OnLButtonUp
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnMouseMove
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnEraseBkgnd
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnSetScrollInfo
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnLButtonDblClk
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);


	LRESULT OnTimer
		(
			UINT uMsg, 
			WPARAM wParam, 
			LPARAM lParam, 
			BOOL& bHandled
		);

	///
	/// Methods
	///

public:

	///
	/// setBuddy
	///
	/// Set control for receiving WM_VSCROLL notifications
	///
	HWND setBuddy( const HWND hWnd );

private:

	///
	/// getUpArrowRect
	///
	/// Get up arrow rectangle
	///
	void calcUpArrowRect( CRect& rect );


	///
	/// getDownArrowRect
	///
	/// Get down arrow rectangle
	///
	void calcDownArrowRect( CRect& rect );


	///
	/// getBackRect
	///
	/// Get back rectangle
	///
	void calcBackRect( CRect& rect );


	///
	/// getScrollWidgetRect
	///
	/// Get scroll widget rectangle
	///
	void calcScrollWidgetRect( CRect& rect );


	///
	/// calcThumbPos
	///
	/// Calculate current thumb position depend on drag position
	///
	int calcThumbPos( const int dragPos );

private:

	///
	/// Possible scroll states
	///
	enum State
	{
		NONE = -1,
		UP_ARROW = 1,
		DOWN_ARROW,
		SCROLL_WIDGET,
		BACK_UP,
		BACK_DOWN
	};

	///
	/// Members
	///

private:

	CBitmap m_Back;

	CBitmap m_UpArrow;

	CBitmap m_DownArrow;

	CBitmap m_ScrollWidget;


	State m_State;
	int m_DragOffset;
	int m_DragPos;

	HWND m_Buddy;

	CPoint m_ClickPos;
	UINT_PTR m_Timer;
};


///
/// setBuddy
///
/// Set control for receiving WM_VSCROLL notifications
///
inline
HWND CMyScrollbar::setBuddy( const HWND hWnd )
{
	const HWND prevBuddy = m_Buddy;

	m_Buddy = hWnd;

	return prevBuddy;
}
