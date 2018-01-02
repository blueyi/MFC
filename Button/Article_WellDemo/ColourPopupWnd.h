#if !defined(AFX_SVIZ_COLOURPOPUP_H__D0B75902_INCLUDED_)
#define AFX_SVIZ_COLOURPOPUP_H__D0B75902_INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif 

#include "basictype.h"
#include "wellBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CSVizColorWell window

class SVIZDLLEXPORT CSVizColorWell : public CSVizWellCtrl
{
	DECLARE_DYNCREATE(CSVizColorWell)
// Construction
public:
    CSVizColorWell();
    CSVizColorWell(DWORD, COLORREF, COLORREF,
                 LPCTSTR szDefaultText = NULL, LPCTSTR szCustomText = NULL,
				 LPCTSTR szEffectText = NULL, LPCTSTR szNoText = NULL);
    void Initialise();

// Attributes
public:

// Operations
public:
//    BOOL Create(CPoint p, CWnd* pParentWnd, DWORD );
    void FindCellFromColour(COLORREF crColour);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CSVizColorWell)
    public:
//    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

// Implementation
public:
	void DrawCell2000(CDC* pDC, int nIndex);
    virtual ~CSVizColorWell();

protected:
    BOOL GetCellRect(int nIndex, const LPRECT& rect);
    void SetWindowSize();
    void ChangeSelection(int nIndex);
    void EndSelection(UINT nMessage);
    void DrawCell(CDC* pDC, int nIndex);

    COLORREF GetColour(int nIndex)              { return m_Colours[nIndex].crColour; }
    CString GetWellName(int nIndex)           { return m_Colours[nIndex].szName; }
    int  GetIndex(int row, int col) const;
    int  GetRow(int nIndex) const;
    int  GetColumn(int nIndex) const;

// protected attributes
protected:

    static ColourTableEntry m_Colours[];

    CString			m_strDefaultText,
					m_strCustomText,
					m_strEffectText,
					m_strNoText;

    CRect			m_CustomTextRect, 
					m_DefaultTextRect, 
					m_EffectTextRect,
					m_NoTextRect;

    CPalette		m_Palette;

    COLORREF		m_crInitialColour,
					m_defaultColor,
					m_crColour;

	
public:
//	void SetBrushProperty(BRUSHPROPERTY&);
	int				m_effectpage;
//	BRUSHPROPERTY	m_Property;
    // Generated message map functions
protected:
    //{{AFX_MSG(CSVizColorWell)
//    afx_msg void OnNcDestroy();
 //   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
//	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/** @class CSVizColorWell
 *  @brief Control for choosing different color. 
 *
 * CSVizColorWell not only allows user to choose different color. It is actually an
 * interface to set all property for a GDI+ Brush. It allows selection of the different
 * brush type: TextureBrush, GradientBrush  and HatchBrush. It uses CEffectDlg to access
 * all the data that to initialized these three type brush. In order to use the CSVizColorWell to
 * set brush, the m_strEffectText must be not empty.
 * 
 * The parent window of CColorPopupWnd is usually CColourPicker. But you can use other as
 * the parent windows, in that case, the gdi+ effect cannot be used.
 *
 * For more information on CSVizColorWell, see CSVizWellCtrl, CEffectDlg and CColourPicker.
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
