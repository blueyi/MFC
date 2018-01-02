#pragma once

#include "Theme.h"

/////////////////////////////////////////////////////////////////////
// CRHTree, 2nd version (Aug 07)
// Written by Paul Roberts, http://www.tlhouse.co.uk
//
// Inspired by Jim Alsup's VividTree article: 
// http://www.codeproject.com/treectrl/VividTree.asp
//
// Use it freely, but please leave this header intact
//

class CRHTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CRHTree)

// Data Members
protected:
	typedef enum 
	{
		eGroupText,
		eGroupBack,
		eItemText,
		eItemBack,
		eWidgetHot
	} TreeColor;

	// Theme stuff
	CTheme							m_Theme;
	BOOL							m_bThemeInited;
	
	// Open/close widget...
	HTREEITEM						m_hWidgetHlt;
	HICON							m_hWidgetExpand;
	HICON							m_hWidgetCollapse;
	HICON							m_hWidgetExpandHot;
	HICON							m_hWidgetCollapseHot;
	COLORREF						m_crWidgetBack;
	
	// Spacers
	int								m_nHSpacer;

// Methods
public:
	CRHTree();
	virtual ~CRHTree();

public:
	virtual void		InvalidateItem( HTREEITEM hItem );
	virtual void		InvalidateAncestors( HTREEITEM hItem );

	// V2 - fix up drawing after possible horz scroll
	virtual BOOL		EnsureVisible( HTREEITEM hItem );

protected:
	// XP/Vista theme support - called on demand
	virtual void		InitTheme();
	
	// Drawing...
	virtual void		DrawBackground( CDC* pDC, CRect rClient );
	virtual void		DrawItems( CDC* pDC, CRect rClient );
	virtual void		DrawItem( CDC* pDC, CRect rClient, HTREEITEM hItem, CRect rItem );
	virtual void		DrawWidget( CDC* pDC, CRect rCell, BOOL bExpanded, BOOL bActive = FALSE );
	virtual void		DrawCheck( CDC* pDC, CRect rCell, int nCheckState );
	virtual void		DrawGroupWash( CDC* pDC, CRect rCell );
	virtual void		DrawGroupTitle( CDC* pDC, CRect rCell, LPCTSTR lpszTitle );
	virtual void		DrawItemTitle( CDC* pDC, CRect rCell, LPCTSTR lpszTitle );
	virtual void		DrawItemImage( CDC* pDC, CRect rCell, HTREEITEM hItem, BOOL bSelected );
	virtual void		OffsetTextRect( CRect& rText );
	virtual void		DrawItemLines( CDC* pDC, HTREEITEM hItem );
	virtual int			CalcHorzSpacer( CDC* pDC );
	virtual BOOL		DrawPNG( UINT nIDPNG, CDC* pDC, int nLeft, int nTop, int nWidth, int nHeight );
	virtual COLORREF	GetPartColor( TreeColor nClr );
	
	// Item state...
	virtual BOOL		IsGroup( HTREEITEM hItem );
	virtual int			GetCheckState( HTREEITEM hItem );
	virtual BOOL		HasImage( HTREEITEM hItem );
	
	// Widget...
	virtual void		PrepareWidgetIcons( CDC* pDC );
	virtual void		DestroyWidgetIcons();
	virtual void		GetWidgetHRange( long& nLeft, long& nRight ); // V2
	virtual BOOL		HitTestWidget( CPoint ptLocal, HTREEITEM& hItem );

	virtual void		HiliteWidget( CPoint ptLocal );
	
	// CheckBoxes...
	virtual BOOL		HitTestCheckBox( CPoint ptLocal, HTREEITEM& hItem );
	

// MFC Stuff below here
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); // V2
	virtual afx_msg BOOL OnToolTipText( UINT id, NMHDR* pNMHDR, LRESULT* pResult );
};


