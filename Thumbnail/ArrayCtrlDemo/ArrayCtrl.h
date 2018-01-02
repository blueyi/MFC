/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// ArrayCtrl.h : interface of the ArrayCtrl class                          //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#if !defined(_ARRAYCTRL_H_INCLUDED_)
#define _ARRAYCTRL_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Microsoft SDK November 2001 not installed
#ifndef TTS_BALLOON
#define TTS_NOANIMATE	0x10
#define TTS_NOFADE		0x20
#define TTS_BALLOON		0x40
#define TTS_CLOSE		0x80
#endif		// TTS_BALLOON

#include "CMemDC.h"

// Control window class name
#define ARRAYCTRL_CLASSNAME		_T("ArrayControlClass")

// Control's styles
#define	CONTROL_MASK_BITS	0x000000FF		// can be enough for this control. CCS_ styles will not be used
#define	WINDOWS_MASK_BITS	0xFFFFFF00		// I hope that windows not uses more than this bits

// control styles
#define	ACS_GRIDLINES		0x00000001		// gridlines required
#define	ACS_TOOLTIP			0x00000002		// tooltip required
#define	ACS_TTBALLOON		0x00000004		// tooltip style is balloon
#define	ACS_BALLOONTIP		ACS_TOOLTIP | ACS_TTBALLOON
#define	ACS_CLIENTEDGE		0x00000010		// client edge required
#define	ACS_USERDATA		0x00000020		// control must manages user data

// internal style flag indicators
#define	ACS_FIXEDCOL		0x01000000		// columns are fixed
#define	ACS_FIXEDROW		0x02000000		// rows are fixed
#define	ACS_NOREDRAW		0x04000000		// redraw flag

// item states 
#define	ACIS_NORMAL			0x00000000		// item is in normal state
#define	ACIS_SELECTED		0x00000001		// item is selected
#define	ACIS_VISIBLE		0x00000002		// item is visible (totally or partially) over current view
#define	ACIS_HIDDEN			0x00000004		// item is not visible (out of current view)

// notification message id
#define	ACN_CLICK			0x00000001		// left button was clicked
#define	ACN_RCLICK			0x00000002		// right button was clicked
#define	ACN_DBCLICK			0x00000004		// left button was double clicked
#define	ACN_NEEDTIPTEXT		0x00000100		// tooltip need text
#define	ACN_DRAWITEM		0x00000200		// item required to be drawn
#define	ACN_DELETEITEM		0x00000400		// item is been deleted

// Add item special item-id
#define	ACAI_TOP			-1				// item must be inserted at top
#define	ACAI_BOTTOM			-2				// item must be added at bottom

// dimensional object type
#define	ACDT_NODIMS			0				// no fixed dimension
#define	ACDT_COLUMNS		1				// dimension is column
#define	ACDT_ROWS			2				// dimension is row

// scrolling object type
#define	ACSO_LINE			1				// object is line
#define	ACSO_PAGE			2				// object is page

// default colors
#define DEFAULT_BACKGROUND_COLOR	RGB(255,255,255)
#define DEFAULT_GRID_COLOR			RGB(192,192,192)


/////////////////////////////////////////////////////////////////////////////
// Global service functions
void BoundsCopy		(LPARAM* pDest, int nDestIndx, LPARAM* pSrc, int nStart, int nEnd);


/////////////////////////////////////////////////////////////////////////////
// CArrayCtrl window

class CArrayCtrl : public CWnd
{
// Construction
public:
	CArrayCtrl();

// Member variables
private:
    CToolTipCtrl*   m_pToolTip;		// tooltip control
	CMemDC*			m_pVirtDC;		// virtual DC (primary memory DC)
	CMemDC*			m_pDrawDC;		// item DC (user painting memory DC)
	CMemDC*			m_pFrameDC;		// frame DC (grid painting memory DC)
	HCURSOR			m_hCursor;		// cursor handle for this control

	UINT			m_nID;			// ID of the control
	BOOL			m_bDrawable;	// control can (TRUE) or cannot (FALSE) draw his items
	DWORD			m_dwStyle;		// control's style
	int				m_nItemHit;		// tooltip hit item
	int				m_nItemsCount;	// items number
	int				m_nWidth;		// VDC width (current view width)
	int				m_nHeight;		// VDC height (current view height)
	int				m_nItemW;		// item width
	int				m_nItemH;		// item height
	int				m_nColumns;		// current columns count
	int				m_nRows;		// current rows count
	int				m_nSelItem;		// item selected
	int				m_nVertLineSize;	// vertical scrolling line size (default is item height)
	int				m_nVertPageSize;	// vertical scrolling page size (default is control's client rect height)
	int				m_nHorzLineSize;	// vertical scrolling line size (default is item width)
	int				m_nHorzPageSize;	// vertical scrolling page size (default is control's client rect width)
	int				m_nVertPos;		// current view vertical scroll position
	int				m_nHorzPos;		// current view horizontal scroll position
	int				m_nVertMax;		// max virtual vertical height
									// number_of_rows * item_height (corrected with grid lines, if any)
	int				m_nHorzMax;		// max virtual horizontal scroll size
									// number_of_columns * item_width (corrected with grid lines, if any)
	int				m_nThickness;	// grid lines thickness
	int				m_nGrid;		// grid lines thickness internal value 
									// is m_nThickness if grid is active, 0 otherwise)
	COLORREF		m_crCtrlBg;		// control background color
	COLORREF		m_crGrid;		// grid color

	LPARAM			m_dwUserData;	// global control user data value
	LPARAM*			m_lpItemVect;	// address of items data vector (store items user data)

// Operations
public:
	BOOL	Create			(DWORD dwStyle, const CRect& rect, CWnd* pParentWnd, UINT nID, const CSize& ItemSize=CSize(0,0));
	UINT	GetCtrlId		() {return m_nID;}
	void	SetCtrlData		(LPARAM dwData) {m_dwUserData = dwData;};
	LPARAM	GetCtrlData		() {return m_dwUserData;};
	void	SetToolTip		(DWORD ttstyle);
	void	SetCursor		(HCURSOR hCursor);
	void	SetRedraw		(BOOL bResize);
	void	Activate		(BOOL bFlag);

	// Items
	void	SetItemCount	(int nItems);
	int		GetItemCount	() {return m_nItemsCount;}
	DWORD	GetItemState	(int nItem);
	int		GetRowIndex		(int nItem);
	int		GetRowIndex		() {return GetRowIndex(m_nSelItem);}
	int		GetColumnIndex	(int nItem);
	int		GetColumnIndex	() {return GetColumnIndex(m_nSelItem);}
	void	AddItem			(int nItem, LPARAM dwData);
	void	AddItem			(LPARAM dwData) {AddItem(ACAI_BOTTOM, dwData);}
	void	DrawItem		(int nItem);
	void	RemoveItem		(int nItem);
	void	RemoveAllItems	();
	LPARAM	SetItemData		(int nItem, LPARAM dwData);
	LPARAM	GetItemData		(int nItem);

	// Sizing and dimensioning
	void	SetItemSize		(int width, int height);
	void	SetItemSize		(CSize* pSize) {SetItemSize(pSize->cx, pSize->cy);}
	void	SetDimension	(int num, int obj);
	void	SetDimension	(int num) {SetDimension(num, (m_dwStyle & ACS_FIXEDCOL? ACDT_COLUMNS: ACDT_ROWS));}
	int		GetDimension	(int* dimtype);
	int		GetWidth		() {return m_nWidth;}
	int		GetHeight		() {return m_nHeight;}
	void	GetItemSize		(CSize* pSize);
	int		GetItemWidth	() {return m_nItemW;}
	int		GetItemHeight	() {return m_nItemH;}
	void	SetColumns		(int ncol) {SetDimension(ncol, ACDT_COLUMNS);}
	void	SetRows			(int nrow) {SetDimension(nrow, ACDT_ROWS);}
	int		GetColumns		() {return m_nColumns;}
	int		GetRows			() {return m_nRows;}

	// Colouring
	void	SetBkColor		(COLORREF crBack);
	void	SetGridColor	(COLORREF crGrid);
	void	SetColors		(COLORREF crBack, COLORREF crGrid);
	COLORREF GetBkColor		() {return m_crCtrlBg;}
	COLORREF GetGridColor	() {return m_crGrid;}
	void	SetTipColor		(COLORREF crBkg, COLORREF crTxt);

	// Selection and Scrolling
	void	SelectItem		(int nItem);
	void	ActivateItem	(int nItem);
	void	ActivateItem	() {ActivateItem(m_nSelItem);}
	int		GetSelectedItem	() {return m_nSelItem;}
	int		GetHitItem		() {return m_nItemHit;}
	void	SetScrollSize	(int nScrollVersus, int nScrollObj, int nSize);
	int		GetScrollSize	(int nScrollVersus, int nScrollObj);
	void	Scroll			(UINT nSBVers, UINT nSBCode);
	void	Scroll			(UINT nSBVers, UINT nSBCode, UINT nPos);
	void	VertScroll		(UINT nSBCode);
	void	VertScroll		(UINT nSBCode, UINT nPos);
	void	HorzScroll		(UINT nSBCode);
	void	HorzScroll		(UINT nSBCode, UINT nPos);
	void	EnsureVisible	(int nItem);
	BOOL	IsVisible		(int nItem);

	// Grid Lines
	void	SetGridLines	(BOOL bActive);
	BOOL	GetGridLines	() {return (m_dwStyle & ACS_GRIDLINES? TRUE: FALSE);}
	void	SetGridThickness(int nThickness);
	int		GetGridThickness() {return m_nThickness;}

private:
	void	AllocateVector	();
	int		HitTest			(int x, int y);
	int		HitTest			(CPoint* pPoint);

	void	VdcCreate		();
	void	VdcInvalidate	();
	void	VdcDelete		();
	void	VdcRedraw		(int nOldItem, int nNewItem);
	void	VdcDraw			();
	void	VdcItemDraw		(CRect* pVdcRect, int nItem);
	void	VdcSetDimensions();
	void	VdcSetScroll	();
	void	VdcUpdate		();
	void	VdcSetDrawable	();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArrayCtrl)
	protected:
	virtual BOOL	PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual			~CArrayCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CArrayCtrl)
	afx_msg void	OnPaint();
	afx_msg void	OnDestroy();
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void	OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void	OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL	OnToolTipText(UINT nId, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//}}AFX_INSERT_LOCATION

/////////////////////////////////////////////////////////////////////////////
// Notification structure for WM_NOTIFY message

// Structure notification for ACN_CLICK, ACN_RCLICK, ACN_DBCLICK
typedef struct tagACITEMACTIVATE
{
	NMHDR			hdr;			// standard header
	CArrayCtrl*		pControl;		// control pointer			
	int				nItem;			// item activate
	DWORD			dwState;		// item state
	int				nRow;			// row (relative to current view)
	int				nColumn;		// column (relative to current view)
	CPoint			ptAction;		// mouse pointer location at event 
	UINT			nKeyFlags;		// modifier key that were pressed
	LPARAM			dwParam;		// user data
}
	ACITEMACTIVATE, *LPACITEMACTIVATE;

// Structure notification for ACN_DRAWITEM, ACN_DELETEITEM
typedef struct tagACITEMINFO
{
	NMHDR			hdr;			// standard header
	CArrayCtrl*		pControl;		// control pointer			
	int				nItem;			// item to be draw
	DWORD			dwState;		// item state
	int				nRow;			// row (relative to current view)
	int				nColumn;		// column (relative to current view)
	CDC*			pDC;			// DC to be draw the item
	int				nWidth;			// width of the given DC
	int				nHeight;		// height of the given DC
	LPARAM			dwParam;		// user data
}
	ACITEMINFO, *LPACITEMINFO;

// Structure notification for ACN_NEEDTIPTEXT
typedef struct tagACTOOLTIPINFO
{
	NMHDR			hdr;			// standard header
	CArrayCtrl*		pControl;		// control pointer			
	int				nItem;			// item to be draw
	DWORD			dwState;		// item state
	int				nRow;			// row (relative to current view)
	int				nColumn;		// column (relative to current view)
	LPTSTR			lpszTipText;	// address of need text buffer
	LPARAM			dwParam;		// user data
}
	ACTOOLTIPINFO, *LPACTOOLTIPINFO;

#endif // !defined(_ARRAYCTRL_H_INCLUDED_)
