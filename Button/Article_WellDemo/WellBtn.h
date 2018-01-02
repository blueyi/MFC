////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2002, SVizSoft, All rights reserved.
//
// FILE:     CSVizWellCtrl.h
//			$Revision: 1.2 $
//			$Date: 2002/11/14 02:43:11 $
//			$Author: tzhu $ of last update
//
// CREATOR:    Tao Zhu
//
// DESCRIPTION
//    Class defination for class CSVizWellCtrl. 
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WELLBTN_H__EBF4CD97_65C2_4F2E_8599_9F1D8A99B2F9__INCLUDED_)
#define AFX_WELLBTN_H__EBF4CD97_65C2_4F2E_8599_9F1D8A99B2F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WellWellWnd.h : header file

SVIZDLLEXPORT extern UINT WELL_SELCHANGED;
SVIZDLLEXPORT extern UINT WELL_DROPDOWN;
SVIZDLLEXPORT extern UINT WELL_CLOSEUP;
SVIZDLLEXPORT extern UINT WELL_SELENDOK;
SVIZDLLEXPORT extern UINT WELL_SELENDCANCEL;
SVIZDLLEXPORT extern UINT CPW_SELCHANGED;

#define WELL_STATE_NORMAL	  0
#define WELL_STATE_SELECTED   1
#define WELL_STATE_FOCUSED	  2


#define WELL_STYLE_CLASSIC		0x0000
#define WELL_STYLE_OFFICE		0x0001
#define WELL_STYLE_DRAW_MASK	0x00ff

#define WELL_STYLE_POPUP		0x0100
#define WELL_STYLE_AUTODELETE	0x0200

#define WELL_STYLE_INPROPLIST	0x8000

#define INVALID_WELL   -1


/////////////////////////////////////////////////////////////////////////////
// CSVizWellCtrl window

class SVIZDLLEXPORT CSVizWellCtrl : public CButton
{
    DECLARE_DYNCREATE(CSVizWellCtrl)
// Construction
public:
	CSVizWellCtrl			();
	CSVizWellCtrl			(DWORD);
public:
	virtual ~CSVizWellCtrl();
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVizWellCtrl)
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

public:
    virtual BOOL	Create			(CPoint, CWnd*, DWORD dwWinStyle = WS_VISIBLE|WS_CHILD);
    void			CreateToolTips	();
    virtual void	Initialise		();
    virtual CString	GetWellName		(int )           { return "well"; }
	virtual void	DrawItem		(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void	DrawCellContent (CDC* pDC, int nIndex, CRect rect,BYTE state);
    virtual void	SetWindowSize	();

	UINT			IsPopupWnd		() {return m_style & WELL_STYLE_POPUP;}
	UINT			IsAutoDelete    () {return m_style & WELL_STYLE_AUTODELETE;}	
	void			SetPopupWnd     (bool b = true);
	void			SetAutoDelete   (bool b = true);
	UINT			GetDrawStyle	() {return m_style & WELL_STYLE_DRAW_MASK;}
	void			SetDrawStyle	(UINT s) { m_style &= 0xffffff00; m_style |= s;}
	void			SetInPropList   (bool b = true);
	UINT			IsInPropList	() {return m_style & WELL_STYLE_INPROPLIST;}

protected:
    virtual BOOL	GetCellRect		(int nIndex, const LPRECT& rect);
    virtual void	FindCellFromWell(int nWell);
    virtual void	ChangeSelection	(int nIndex);
    virtual void	EndSelection	(UINT nMessage);
    virtual void	DrawCell		(CDC* pDC, int nIndex);

    int				GetIndex		(int row, int col) const;
    int				GetRow			(int nIndex) const;
    int				GetColumn		(int nIndex) const;
 

// protected attributes
protected:
    int				m_nNumColours;
    int				m_nNumColumns, m_nNumRows;
    int				m_nMargin;
    int				m_nCurrentSel;
    int				m_nChosenWellSel;
    CRect			m_WindowRect;
	CSize			m_nBoxSize;
    CToolTipCtrl	m_ToolTip;

public:
	UINT			m_style;
	int				m_crWell,
					m_nNumWells,
					m_crInitialWell;

    CWnd*			m_pParent;
	CRect			m_ParentRect;
    Color			m_foreColor;
	Color			m_backColor;
	BrushType		m_BrushType;


	int				m_count;

    CFont			m_Font;
//	BOOL		    m_bAutoDeleted;
//	BOOL			m_bPopUp;
	// Generated message map functions
protected:
	//{{AFX_MSG(CSVizWellCtrl)
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
    afx_msg void OnNcDestroy();
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/** @class CSVizWellCtrl
 *  @brief Base class for all well-like button or popup window. It cannot be instantialized. User
 * has to user class that derived from this class.
 *
 * The CSVizWellCtrl class provides the basic functionality for user-defined
 * well controls used in dialog. It also can be used as popup window.
 * 
 * CSVizWellCtrl supports functions such as highlighting the current focusing
 * well and selected well. CSVizWellCtrl send message to the parent windows
 * when selection is changed, confirmed or cancelled.
 *
 * For more information on CSVizWellCtrl, see CSVizHatchWell, CSVizColorWell, 
 * CSVizLineStyleWell and CSVizArrowWell.
 */

#endif 
///////////////////////////////////////////////////////////////////////
// This file is a part of the SViz MFC Extention Class.
// 2001-2002 SVizSoft Software, All Rights Reserved.
//
// SVIZSOFT GRANTS TO YOU THE LIMITED RIGHT TO USE THIS SOFTWARE ON 
// A SINGLE COMPUTER. 
// THESE SOURCE FILE ARE CONSIDERED CONFIDENTIONAL AND ARE THE PROPERTY
// OF SVIZSOFT AND ARE NOT TO BE RE-DISTRIBUTED BY ANY MEANS WHATSOEVER
// WITHOUT THE EXPRESSED WRITTEN CONSENT OF SVIZ SOFTWARE.
// 
// You can contact us.
// admin@svizsoft.com
///////////////////////////////////////////////////////////////////////
